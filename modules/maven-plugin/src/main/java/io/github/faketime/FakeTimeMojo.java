package io.github.faketime;

import static org.apache.maven.plugins.annotations.LifecyclePhase.VALIDATE;
import static org.codehaus.plexus.util.Os.OS_ARCH;
import static org.codehaus.plexus.util.Os.OS_NAME;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.stream.Stream;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.shared.transfer.artifact.ArtifactCoordinate;
import org.apache.maven.shared.transfer.artifact.DefaultArtifactCoordinate;
import org.apache.maven.shared.transfer.artifact.resolve.ArtifactResolver;
import org.apache.maven.shared.transfer.artifact.resolve.ArtifactResolverException;
import org.codehaus.plexus.archiver.UnArchiver;
import org.codehaus.plexus.archiver.manager.ArchiverManager;
import org.codehaus.plexus.archiver.manager.NoSuchArchiverException;
import org.codehaus.plexus.components.io.fileselectors.FileSelector;
import org.codehaus.plexus.components.io.fileselectors.IncludeExcludeFileSelector;

/**
 * @threadSafe
 */
@Mojo(name="prepare", defaultPhase = VALIDATE)
public class FakeTimeMojo extends AbstractMojo {

  private static final String GROUP_ID = "io.github.faketime-java";
  private static final String ARTIFACT_ID = "faketime-maven-plugin";
  private static final String AGENT_ARTIFACT_ID = "faketime-agent";

  private static final String ARG_LINE_PROPERTY_NAME = "faketime.argLine";

  @Component
  private ArtifactResolver artifactResolver;

  @Component
  private ArchiverManager archiverManager;

  @Parameter(defaultValue = "${session}", readonly = true)
  private MavenSession session;

  @Override
  public void execute() throws MojoFailureException {
    if (getOs() == null || Os.getBitness() == null) {
      getLog().warn(String.format("!!! %s %s is not supported by FakeTime !!!", OS_NAME, OS_ARCH));
      return;
    }

    unpackAgent();
    setArgLineProperty();
  }

  private void unpackAgent() {
    try {
      Artifact artifact = artifactResolver.resolveArtifact(session.getProjectBuildingRequest(), getAgentArtifactCoordinate()).getArtifact();

      getTargetDirectory().mkdirs();

      UnArchiver unArchiver = archiverManager.getUnArchiver(artifact.getType());
      unArchiver.setSourceFile(artifact.getFile());
      unArchiver.setDestDirectory(getTargetDirectory());
      unArchiver.setFileSelectors(getAgentBinaryFileSelector());
      unArchiver.extract();
    }
    catch (ArtifactResolverException | NoSuchArchiverException e) {
      throw new RuntimeException(e);
    }
  }

  private void setArgLineProperty() {
    session.getCurrentProject().getProperties().setProperty(ARG_LINE_PROPERTY_NAME, getAgentJvmArguments());
  }

  private ArtifactCoordinate getAgentArtifactCoordinate() {
    DefaultArtifactCoordinate coordinate = new DefaultArtifactCoordinate();
    coordinate.setGroupId(GROUP_ID);
    coordinate.setArtifactId(AGENT_ARTIFACT_ID);
    coordinate.setVersion(getPluginVersion());
    coordinate.setClassifier(getOs().getClassifierName() + Os.getBitness());
    return coordinate;
  }

  private File getTargetDirectory() {
    return new File(session.getCurrentProject().getBuild().getDirectory());
  }

  private FileSelector[] getAgentBinaryFileSelector() {
    IncludeExcludeFileSelector fileSelector = new IncludeExcludeFileSelector();
    fileSelector.setIncludes(new String[] { getOs().getAgentBinaryName() });
    return new IncludeExcludeFileSelector[] { fileSelector };
  }

  private String getPluginVersion() {
    try {
      try (InputStream is = getClass().getResourceAsStream("/META-INF/maven/" + GROUP_ID + "/" + ARTIFACT_ID + "/pom.properties")) {
        Properties properties = new Properties();
        properties.load(is);
        return properties.getProperty("version");
      }
    }
    catch (IOException e) {
      throw new RuntimeException(e);
    }
  }

  private String getAgentJvmArguments() {
    return String.join(" ",
        "-agentpath:" + new File(getTargetDirectory(), getOs().getAgentBinaryName()).getAbsolutePath(),
        "-XX:+UnlockDiagnosticVMOptions",
        "-XX:DisableIntrinsic=_currentTimeMillis",
        "-XX:CompileCommand=quiet",
        "-XX:CompileCommand=exclude,java/lang/System.currentTimeMillis");
  }

  private Os getOs() {
    return Stream.of(Os.values()).filter(Os::isCurrent).findFirst().orElse(null);
  }
}
