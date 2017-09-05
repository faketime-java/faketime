import static org.assertj.core.api.Assertions.assertThat;

import org.junit.Rule;
import org.junit.Test;

import io.github.faketime.FakeTimeMixin;
import io.github.faketime.FakeTimeRule;

public class FakeTimeRuleTest implements FakeTimeMixin {

  @Rule
  public FakeTimeRule rule = new FakeTimeRule();

  @Test
  public void test1() {
    assertThat(System.currentTimeMillis()).isNotEqualTo(0L);

    stopTimeAt(0L);
  }

  @Test
  public void test2() {
    assertThat(System.currentTimeMillis()).isNotEqualTo(0L);

    stopTimeAt(0L);
  }
}
