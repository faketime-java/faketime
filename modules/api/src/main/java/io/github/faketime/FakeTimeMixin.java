package io.github.faketime;

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.OffsetDateTime;
import java.time.ZoneId;
import java.time.ZonedDateTime;
import java.time.temporal.TemporalAmount;

public interface FakeTimeMixin {

  default void stopTimeAt(long epochMillisecond) {
    FakeTime.stopAt(epochMillisecond);
  }

  default void stopTimeAt(Instant instant) {
    FakeTime.stopAt(instant);
  }

  default void stopTimeAt(ZonedDateTime zonedDateTime) {
    FakeTime.stopAt(zonedDateTime);
  }

  default void stopTimeAt(OffsetDateTime offsetDateTime) {
    FakeTime.stopAt(offsetDateTime);
  }

  default void stopTimeAt(LocalDateTime localDateTime) {
    FakeTime.stopAt(localDateTime);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, int minute, int second, int millisecond, ZoneId zone) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, minute, second, millisecond, zone);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, int minute, int second, ZoneId zone) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, minute, second, zone);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, int minute, ZoneId zone) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, minute, zone);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, ZoneId zone) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, zone);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, ZoneId zone) {
    FakeTime.stopAt(year, month, dayOfMonth, zone);
  }

  default void stopTimeAtUtc(int year, int month, int dayOfMonth, int hour, int minute, int second, int millisecond) {
    FakeTime.stopAtUtc(year, month, dayOfMonth, hour, minute, second, millisecond);
  }

  default void stopTimeAtUtc(int year, int month, int dayOfMonth, int hour, int minute, int second) {
    FakeTime.stopAtUtc(year, month, dayOfMonth, hour, minute, second);
  }

  default void stopTimeAtUtc(int year, int month, int dayOfMonth, int hour, int minute) {
    FakeTime.stopAtUtc(year, month, dayOfMonth, hour, minute);
  }

  default void stopTimeAtUtc(int year, int month, int dayOfMonth, int hour) {
    FakeTime.stopAtUtc(year, month, dayOfMonth, hour);
  }

  default void stopTimeAtUtc(int year, int month, int dayOfMonth) {
    FakeTime.stopAtUtc(year, month, dayOfMonth);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, int minute, int second, int millisecond) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, minute, second, millisecond);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, int minute, int second) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, minute, second);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour, int minute) {
    FakeTime.stopAt(year, month, dayOfMonth, hour, minute);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth, int hour) {
    FakeTime.stopAt(year, month, dayOfMonth, hour);
  }

  default void stopTimeAt(int year, int month, int dayOfMonth) {
    FakeTime.stopAt(year, month, dayOfMonth);
  }

  default void offsetTimeBy(long milliseconds) {
    FakeTime.offsetBy(milliseconds);
  }

  default void offsetTimeBySeconds(int seconds) {
    FakeTime.offsetBySeconds(seconds);
  }

  default void offsetTimeByMinutes(int minutes) {
    FakeTime.offsetByMinutes(minutes);
  }

  default void offsetTimeByHours(int hours) {
    FakeTime.offsetByHours(hours);
  }

  default void offsetTimeByDays(int days) {
    FakeTime.offsetByDays(days);
  }

  default void offsetTimeBy(TemporalAmount temporalAmount) {
    FakeTime.offsetBy(temporalAmount);
  }

  default void restoreRealTime() {
    FakeTime.restoreReal();
  }
}
