package io.github.faketime;

import static java.util.Arrays.asList;
import static java.util.Collections.singletonList;
import static org.codehaus.plexus.util.Os.OS_ARCH;
import static org.codehaus.plexus.util.Os.OS_NAME;

import java.util.List;

public enum Os {

  WINDOWS("windows", "windows", "faketime.dll"),
  LINUX("linux", "linux", "libfaketime"),
  MAC(asList("mac", "osx"), "mac", "libfaketime");

  private final List<String> names;
  private final String classifierName;
  private final String agentBinaryName;

  Os(List<String> names, String classifierName, String agentBinaryName) {
    this.names = names;
    this.classifierName = classifierName;
    this.agentBinaryName = agentBinaryName;
  }

  Os(String name, String classifierName, String agentBinaryName) {
    this(singletonList(name), classifierName, agentBinaryName);
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
    return names.stream().anyMatch(OS_NAME::contains);
  }
}
