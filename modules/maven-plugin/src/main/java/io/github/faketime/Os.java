package io.github.faketime;

import static org.codehaus.plexus.util.Os.OS_ARCH;
import static org.codehaus.plexus.util.Os.OS_NAME;

import java.util.stream.Stream;

public enum Os {
  WINDOWS(new String[] { "windows" }, "windows", "faketime.dll"),
  LINUX(new String[] { "linux" }, "linux", "libfaketime"),
  MAC(new String[] { "mac", "osx" }, "mac", "libfaketime");

  private final String[] names;
  private final String classifierName;
  private final String agentBinaryName;

  private Os(String[] names, String classifierName, String agentBinaryName) {
    this.names = names;
    this.classifierName = classifierName;
    this.agentBinaryName = agentBinaryName;
  }

  public static String getBitness() {
    switch (OS_ARCH.replace("_", "")) {
      case "x8664":
      case "amd64":
      case "ia32e":
      case "em64t":
      case "x64":
        return "64";
      case "x8632":
      case "x86":
      case "i386":
      case "i486":
      case "i586":
      case "i686":
      case "ia32":
      case "x32":
        return "32";
      default:
        return null;
    }
  }

  public String getClassifierName() {
    return classifierName;
  }

  public String getAgentBinaryName() {
    return agentBinaryName;
  }

  public boolean isCurrent() {
    return Stream.of(names).anyMatch(OS_NAME::contains);
  }
}
