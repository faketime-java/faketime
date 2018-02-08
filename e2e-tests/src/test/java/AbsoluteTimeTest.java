import static java.lang.System.currentTimeMillis;
import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatIllegalStateException;

import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.OffsetDateTime;
import java.time.ZoneId;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;

import org.junit.Rule;
import org.junit.Test;

import io.github.faketime.FakeTimeMixin;
import io.github.faketime.FakeTimeRule;

public class AbsoluteTimeTest implements FakeTimeMixin {

  @Rule
  public FakeTimeRule rule = new FakeTimeRule();

  @Test
  public void stopTimeAt_epochMillisecond() {
    stopTimeAt(0);
    assertThat(System.currentTimeMillis()).isEqualTo(0);

    stopTimeAt(20);
    assertThat(System.currentTimeMillis()).isEqualTo(20);
  }

  @Test
  public void stopTimeAt_Instant() {
    stopTimeAt(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC).toInstant());

    assertThat(ZonedDateTime.now(ZoneOffset.UTC))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC));
  }

  @Test
  public void stopTimeAt_ZonedDateTime() {
    stopTimeAt(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC));

    assertThat(ZonedDateTime.now(ZoneOffset.UTC))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC));
  }

  @Test
  public void stopTimeAt_OffsetDateTime() {
    stopTimeAt(OffsetDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC));

    assertThat(OffsetDateTime.now(ZoneOffset.UTC))
        .isEqualTo(OffsetDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC));
  }

  @Test
  public void stopTimeAt_LocalDateTime() {
    stopTimeAt(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));

    assertThat(LocalDateTime.now())
        .isEqualTo(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));
  }

  @Test
  public void stopTimeAt_7() {
    stopTimeAt(2000, 10, 9, 8, 7, 6, 5);

    assertThat(LocalDateTime.now())
        .isEqualTo(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));
  }

  @Test
  public void stopTimeAt_6() {
    stopTimeAt(2000, 10, 9, 8, 7, 6);

    assertThat(ZonedDateTime.now())
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 0, ZoneId.systemDefault()));
  }

  @Test
  public void stopTimeAt_5() {
    stopTimeAt(2000, 10, 9, 8, 7);

    assertThat(OffsetDateTime.now())
        .isEqualTo(OffsetDateTime.of(2000, 10, 9, 8, 7, 0, 0, ZoneId.systemDefault().getRules().getOffset(LocalDateTime.now())));
  }

  @Test
  public void stopTimeAt_4() {
    stopTimeAt(2000, 10, 9, 8);

    assertThat(LocalDateTime.now())
        .isEqualTo(LocalDateTime.of(2000, 10, 9, 8, 0, 0, 0));
  }

  @Test
  public void stopTimeAt_3() {
    stopTimeAt(2000, 10, 9);

    assertThat(LocalDateTime.now())
        .isEqualTo(LocalDateTime.of(2000, 10, 9, 0, 0, 0, 0));
    assertThat(LocalDate.now())
        .isEqualTo(LocalDate.of(2000, 10, 9));
  }


  @Test
  public void stopTimeAtUtc_7() {
    stopTimeAtUtc(2000, 10, 9, 8, 7, 6, 5);

    assertThat(ZonedDateTime.now(ZoneOffset.UTC))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneOffset.UTC));
  }

  @Test
  public void stopTimeAtUtc_6() {
    stopTimeAtUtc(2000, 10, 9, 8, 7, 6);

    assertThat(LocalDateTime.now(ZoneOffset.UTC))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 0, ZoneOffset.UTC).toLocalDateTime());
  }

  @Test
  public void stopTimeAtUtc_5() {
    stopTimeAtUtc(2000, 10, 9, 8, 7);

    assertThat(OffsetDateTime.now(ZoneOffset.UTC))
        .isEqualTo(OffsetDateTime.of(2000, 10, 9, 8, 7, 0, 0, ZoneOffset.UTC));
  }

  @Test
  public void stopTimeAtUtc_4() {
    stopTimeAtUtc(2000, 10, 9, 8);

    assertThat(ZonedDateTime.now(ZoneOffset.UTC))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 0, 0, 0, ZoneOffset.UTC));
  }

  @Test
  public void stopTimeAtUtc_3() {
    stopTimeAtUtc(2000, 10, 9);

    assertThat(ZonedDateTime.now(ZoneOffset.UTC))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 0, 0, 0, 0, ZoneOffset.UTC));
  }


  @Test
  public void stopTimeAt_withZone_7() {
    stopTimeAt(2000, 10, 9, 8, 7, 6, 5, ZoneId.of("Europe/Tallinn"));

    assertThat(ZonedDateTime.now(ZoneId.of("Europe/Tallinn")))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000, ZoneId.of("Europe/Tallinn")));
  }

  @Test
  public void stopTimeAt_withZone_6() {
    stopTimeAt(2000, 10, 9, 8, 7, 6, ZoneId.of("Europe/Tallinn"));

    assertThat(LocalDateTime.now(ZoneId.of("Europe/Tallinn")))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 7, 6, 0, ZoneId.of("Europe/Tallinn")).toLocalDateTime());
  }

  @Test
  public void stopTimeAt_withZone_5() {
    stopTimeAt(2000, 10, 9, 8, 7, ZoneId.of("Europe/Tallinn"));

    assertThat(OffsetDateTime.now(ZoneId.of("Europe/Tallinn")))
        .isEqualTo(OffsetDateTime.of(2000, 10, 9, 8, 7, 0, 0, ZoneId.of("Europe/Tallinn").getRules().getOffset(LocalDateTime.now())));
  }

  @Test
  public void stopTimeAt_withZone_4() {
    stopTimeAt(2000, 10, 9, 8, ZoneId.of("Europe/Tallinn"));

    assertThat(ZonedDateTime.now(ZoneId.of("Europe/Tallinn")))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 8, 0, 0, 0, ZoneId.of("Europe/Tallinn")));
  }

  @Test
  public void stopTimeAt_withZone_3() {
    stopTimeAt(2000, 10, 9, ZoneId.of("Europe/Tallinn"));

    assertThat(ZonedDateTime.now(ZoneId.of("Europe/Tallinn")))
        .isEqualTo(ZonedDateTime.of(2000, 10, 9, 0, 0, 0, 0, ZoneId.of("Europe/Tallinn")));
  }


  @Test
  public void offsetStoppedTimeBy_milliseconds() {
    stopTimeAt(1_000_000);

    offsetStoppedTimeBy(1);
    offsetStoppedTimeBy(234567);

    assertThat(currentTimeMillis()).isEqualTo(1_234_567);
  }

  @Test
  public void offsetStoppedTimeBy_seconds() {
    stopTimeAt(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));

    offsetStoppedTimeBySeconds(1);
    offsetStoppedTimeBySeconds(56);

    assertThat(LocalDateTime.now()).isEqualTo(LocalDateTime.of(2000, 10, 9, 8, 8, 2, 5_000_000));
  }

  @Test
  public void offsetStoppedTimeBy_minutes() {
    stopTimeAt(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));

    offsetStoppedTimeByMinutes(1);
    offsetStoppedTimeByMinutes(56);

    assertThat(LocalDateTime.now()).isEqualTo(LocalDateTime.of(2000, 10, 9, 9, 3, 6, 5_000_000));
  }

  @Test
  public void offsetStoppedTimeBy_hours() {
    stopTimeAt(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));

    offsetStoppedTimeByHours(1);
    offsetStoppedTimeByHours(23);

    assertThat(LocalDateTime.now()).isEqualTo(LocalDateTime.of(2000, 10, 10, 7, 7, 6, 5_000_000));
  }

  @Test
  public void offsetStoppedTimeBy_days() {
    stopTimeAt(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));

    offsetStoppedTimeByDays(1);
    offsetStoppedTimeByDays(30);

    assertThat(LocalDateTime.now()).isEqualTo(LocalDateTime.of(2000, 11, 8, 8, 7, 6, 5_000_000));
  }

  @Test
  public void offsetStoppedTimeBy_duration() {
    stopTimeAt(LocalDateTime.of(2000, 10, 9, 8, 7, 6, 5_000_000));

    offsetStoppedTimeBy(Duration.ofMinutes(1));
    offsetStoppedTimeBy(Duration.ofMinutes(56));

    assertThat(LocalDateTime.now()).isEqualTo(LocalDateTime.of(2000, 10, 9, 9, 3, 6, 5_000_000));
  }


  @Test
  public void offsetStoppedTimeBy_milliseconds_throwsIfNotStopped() {
    assertThatIllegalStateException()
        .isThrownBy(() -> offsetStoppedTimeBy(234567))
        .withMessage("In order to offset stopped time you must first stop the time using one of stopAt*() methods");
  }

  @Test
  public void offsetStoppedTimeBy_seconds_throwsIfNotStopped() {
    assertThatIllegalStateException()
        .isThrownBy(() -> offsetStoppedTimeBySeconds(56))
        .withMessage("In order to offset stopped time you must first stop the time using one of stopAt*() methods");
  }

  @Test
  public void offsetStoppedTimeBy_minutes_throwsIfNotStopped() {
    assertThatIllegalStateException()
        .isThrownBy(() -> offsetStoppedTimeByMinutes(56))
        .withMessage("In order to offset stopped time you must first stop the time using one of stopAt*() methods");
  }

  @Test
  public void offsetStoppedTimeBy_hours_throwsIfNotStopped() {
    assertThatIllegalStateException()
        .isThrownBy(() -> offsetStoppedTimeByHours(23))
        .withMessage("In order to offset stopped time you must first stop the time using one of stopAt*() methods");
  }

  @Test
  public void offsetStoppedTimeBy_days_throwsIfNotStopped() {
    assertThatIllegalStateException()
        .isThrownBy(() -> offsetStoppedTimeByDays(30))
        .withMessage("In order to offset stopped time you must first stop the time using one of stopAt*() methods");
  }

  @Test
  public void offsetStoppedTimeBy_duration_throwsIfNotStopped() {
    assertThatIllegalStateException()
        .isThrownBy(() -> offsetStoppedTimeBy(Duration.ofMinutes(56)))
        .withMessage("In order to offset stopped time you must first stop the time using one of stopAt*() methods");
  }
}
