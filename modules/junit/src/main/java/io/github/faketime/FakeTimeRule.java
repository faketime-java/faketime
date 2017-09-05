package io.github.faketime;

import org.junit.rules.ExternalResource;

public class FakeTimeRule extends ExternalResource implements FakeTimeMixin {

  @Override
  protected void after() {
    restoreRealTime();
  }
}
