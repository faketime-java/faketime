# FakeTime for Java
> FakeTime uses a native Java agent to replace `System.currentTimeMillis()` implementation with the one you can control using system properties.

> Inspired by [arvindsv/faketime](https://github.com/arvindsv/faketime).

[![Build Status](https://travis-ci.org/faketime-java/faketime.svg?branch=master)](https://travis-ci.org/faketime-java/faketime)

```java
public class ExamRegistrationServiceTest implements FakeTimeMixin {
  
  @Autowired
  ExamRegistrationService examRegistrationService;
  
  @Test
  public void registrationExpiresAfterGivenPeriod() {
    ExamRegistration registration = examRegistrationService.openRegistrationValidFor(Duration.ofDays(5));
    
    offsetRealTimeByDays(5);
    
    assertThat(registration.hasExpired()).isTrue();
  }
  
  @Test
  public void registrationIsValidDuringGivenPeriod() {
    ExamRegistration registration = examRegistrationService.openRegistrationValidFor(Duration.ofDays(5));
      
    offsetRealTimeBy(Duration.ofDays(5).minusMinutes(1));
      
    assertThat(registration.hasExpired()).isFalse();
  }
  
  @After
  public void restoreRealTimeAfterTest() {
    restoreRealTime();
  }
}
```

## Manual setup
Start faking time in 4 easy steps:
1. Download the `faketime-agent.jar` for your operating system from the [Maven Central](https://mvnrepository.com/artifact/io.github.faketime-java/faketime-agent) repository.
```xml
<!-- Windows 32bit -->
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-agent</artifactId>
  <version>0.1.0</version>
  <classifier>windows32</classifier>
</dependency>

<!-- Windows 64bit -->
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-agent</artifactId>
  <version>0.1.0</version>
  <classifier>windows64</classifier>
</dependency>

<!-- macOS 32bit -->
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-agent</artifactId>
  <version>0.1.0</version>
  <classifier>mac32</classifier>
</dependency>

<!-- macOS 64bit -->
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-agent</artifactId>
  <version>0.1.0</version>
  <classifier>mac64</classifier>
</dependency>

<!-- Linux 32bit -->
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-agent</artifactId>
  <version>0.1.0</version>
  <classifier>linux32</classifier>
</dependency>

<!-- Linux 64bit -->
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-agent</artifactId>
  <version>0.1.0</version>
  <classifier>linux64</classifier>
</dependency>
```
2. Unpack the `jar` to get the agent, which is `faketime.dll` on Windows and `libfaketime` on other systems.
3. Attach the agent to your Java program with following JVM arguments.
```bash
-agentpath:path/to/unpacked/faketime/binary
-XX:+UnlockDiagnosticVMOptions
-XX:DisableIntrinsic=_currentTimeMillis
-XX:CompileCommand=quiet
-XX:CompileCommand=exclude,java/lang/System.currentTimeMillis
```
4. Use system properties to manipulate `System.currentTimeMillis()`.
```java
System.out.println(System.currentTimeMillis()); // 1234567890
System.setProperty("faketime.offset.ms", "-7890");
System.out.println(System.currentTimeMillis()); // 1234560000

System.setProperty("faketime.absolute.ms", "12345");
System.out.println(System.currentTimeMillis()); // 12345
```
## Java 8 API
```xml
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-api</artifactId>
  <version>0.1.0</version>
  <scope>test</scope>
</dependency>
```
In case you get tired of converting everything to milliseconds there is a Java Time based API.
```java
FakeTime.stopAt(LocalDateTime.of(2000, 11, 10, 9, 8, 7));
FakeTime.stopAt(2000, 11, 10, ZoneOffset.UTC);
FakeTime.offsetRealByMinutes(100);
FakeTime.offsetRealBy(Duration.ofHours(20));
FakeTime.restoreReal();
```
And in case you get annoyed by writing `FakeTime` all the time there is a handy mixin.
```java
public class MyTest implements FakeTimeMixin {
  
  @Test
  public void someTimeTest() {
    stopTimeAt(LocalDateTime.of(2000, 11, 10, 9, 8, 7));
    stopTimeAt(2000, 11, 10, ZoneOffset.UTC);
    offsetRealTimeByMinutes(100);
    offsetRealTimeBy(Duration.ofHours(20));
  }
  
  @After
  public void restoreRealTimeAfterTest() {
    restoreRealTime();
  }
}
```
## JUnit rule
```xml
<dependency>
  <groupId>io.github.faketime-java</groupId>
  <artifactId>faketime-junit</artifactId>
  <version>0.1.0</version>
  <scope>test</scope>
</dependency>
```
This rule calls `FakeTime.restoreReal()` after every test, so you don't have to.

_Note: when using `faketime-junit` you don't need to add `faketime-api` as a `test` dependency_
```java
public class MyTest implements FakeTimeMixin {
  
  @Rule
  public FakeTimeRule fakeTimeRule = new FakeTimeRule();
  
  @Test
  public void someTimeTest() {
    stopTimeAt(2000, 11, 10);
    
    assertThat(LocalDate.now()).isEqualTo(LocalDate.of(2000, 11, 10));
    
    // next test will start with real time
  }
}
```
## Maven plugin
For further convenience there is a Maven plugin that downloads and unpacks the correct agent for your operating system.
It then sets a property that you can use in `surefire` or `failsafe` plugins to attach the agent.

> Full example [here](https://github.com/faketime-java/faketime/blob/master/e2e-tests/pom.xml)
```xml
<build>
  <plugins>
    <plugin>
      <groupId>org.apache.maven.plugins</groupId>
      <artifactId>maven-surefire-plugin</artifactId>
      <version>2.20</version>
      <configuration>
        <argLine>${faketime.argLine}</argLine>
      </configuration>
    </plugin>
    
    <plugin>
      <groupId>io.github.faketime-java</groupId>
      <artifactId>faketime-maven-plugin</artifactId>
      <version>0.1.0</version>
      <executions>
        <execution>
          <goals>
            <goal>prepare</goal>
          </goals>
        </execution>
      </executions>
    </plugin>
  </plugins>
</build>
```
## Maven + IntelliJ
IntelliJ has a cool feature that reads `argLine` from `pom.xml` and adds all arguments to the IDE test runner.
The only thing you need to do is to replace `${faketime.argLine}` with literal arguments, since IntelliJ is not aware of `${faketime.argLine}`.

_Note: before running tests from IntelliJ make sure `faketime-maven-plugin` has downloaded the agent, otherwise tests won't start_

> Full example [here](https://github.com/faketime-java/faketime/blob/master/e2e-tests/pom.xml)
```xml
<properties>
  <faketime.binary>libfaketime</faketime.binary>
</properties>

<profiles>
  <profile>
    <id>faketimeBinary</id>
    <activation>
      <os>
        <family>windows</family>
      </os>
    </activation>
    <properties>
      <faketime.binary>faketime.dll</faketime.binary>
    </properties>
  </profile>
</profiles>

<build>
  <plugins>
    <plugin>
      <groupId>org.apache.maven.plugins</groupId>
      <artifactId>maven-failsafe-plugin</artifactId>
      <version>2.20</version>
      <configuration>
        <argLine>
          -agentpath:${project.build.directory}/${faketime.binary}
          -XX:+UnlockDiagnosticVMOptions
          -XX:DisableIntrinsic=_currentTimeMillis
          -XX:CompileCommand=quiet
          -XX:CompileCommand=exclude,java/lang/System.currentTimeMillis
        </argLine>
      </configuration>
    </plugin>
    
    <plugin>
      <groupId>io.github.faketime-java</groupId>
      <artifactId>faketime-maven-plugin</artifactId>
      <version>0.1.0</version>
      <executions>
        <execution>
          <goals>
            <goal>prepare</goal>
          </goals>
        </execution>
      </executions>
    </plugin>
  </plugins>
</build>
```
## Maven + Eclipse
_Note: before running tests from Eclipse make sure `faketime-maven-plugin` has downloaded the agent, otherwise tests won't start_

`Preferences > Java > Installed JREs > Select > Edit > Default VM arguments`
```bash
# if you're on Windows
-agentpath:target/faketime.dll
-XX:+UnlockDiagnosticVMOptions
-XX:DisableIntrinsic=_currentTimeMillis
-XX:CompileCommand=quiet
-XX:CompileCommand=exclude,java/lang/System.currentTimeMillis

# if you're on macOS/Linux
-agentpath:target/libfaketime
-XX:+UnlockDiagnosticVMOptions
-XX:DisableIntrinsic=_currentTimeMillis
-XX:CompileCommand=quiet
-XX:CompileCommand=exclude,java/lang/System.currentTimeMillis
```
## Gradle
There are no instructions for Gradle yet, but if you'll figure this out, then don't be shy to make a pull request.
Basically, you need to download and unpack the correct agent artifact and then add some JVM arguments to the test runner.
