import static java.lang.System.currentTimeMillis;
import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.data.Offset.offset;

import java.time.Duration;

import org.junit.Rule;
import org.junit.Test;

import io.github.faketime.FakeTimeMixin;
import io.github.faketime.FakeTimeRule;

public class OffsetTimeTest implements FakeTimeMixin {

  @Rule
  public FakeTimeRule rule = new FakeTimeRule();

  @Test
  public void milliseconds() {
    long currentMillis = currentTimeMillis();

    offsetTimeBy(5_000_000);

    assertThat(currentTimeMillis()).isCloseTo(currentMillis + 5_000_000, offset(100L));
  }

  @Test
  public void seconds() {
    long currentMillis = currentTimeMillis();

    offsetTimeBySeconds(2_000);

    assertThat(currentTimeMillis()).isCloseTo(currentMillis + 2_000 * 1_000, offset(100L));
  }

  @Test
  public void minutes() {
    long currentMillis = currentTimeMillis();

    offsetTimeByMinutes(100);

    assertThat(currentTimeMillis()).isCloseTo(currentMillis + 100 * 60 * 1_000, offset(100L));
  }

  @Test
  public void hours() {
    long currentMillis = currentTimeMillis();

    offsetTimeByHours(3);

    assertThat(currentTimeMillis()).isCloseTo(currentMillis + 3 * 60 * 60 * 1_000, offset(100L));
  }

  @Test
  public void days() {
    long currentMillis = currentTimeMillis();

    offsetTimeByDays(5);

    assertThat(currentTimeMillis()).isCloseTo(currentMillis + 5 * 24 * 60 * 60 * 1_000, offset(100L));
  }

  @Test
  public void duration() {
    long currentMillis = currentTimeMillis();

    offsetTimeBy(Duration.ofMinutes(100));

    assertThat(currentTimeMillis()).isCloseTo(currentMillis + 100 * 60 * 1_000, offset(100L));
  }
}
