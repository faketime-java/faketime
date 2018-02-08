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

  default void offsetStoppedTimeBy(long milliseconds) {
    FakeTime.offsetStoppedBy(milliseconds);
  }

  default void offsetStoppedTimeBySeconds(long seconds) {
    FakeTime.offsetStoppedBySeconds(seconds);
  }

  default void offsetStoppedTimeByMinutes(long minutes) {
    FakeTime.offsetStoppedByMinutes(minutes);
  }

  default void offsetStoppedTimeByHours(long hours) {
    FakeTime.offsetStoppedByHours(hours);
  }

  default void offsetStoppedTimeByDays(long days) {
    FakeTime.offsetStoppedByDays(days);
  }

  default void offsetStoppedTimeBy(TemporalAmount amountToAdd) {
    FakeTime.offsetStoppedBy(amountToAdd);
  }

  default void offsetRealTimeBy(long milliseconds) {
    FakeTime.offsetRealBy(milliseconds);
  }

  default void offsetRealTimeBySeconds(long seconds) {
    FakeTime.offsetRealBySeconds(seconds);
  }

  default void offsetRealTimeByMinutes(long minutes) {
    FakeTime.offsetRealByMinutes(minutes);
  }

  default void offsetRealTimeByHours(long hours) {
    FakeTime.offsetRealByHours(hours);
  }

  default void offsetRealTimeByDays(long days) {
    FakeTime.offsetRealByDays(days);
  }

  default void offsetRealTimeBy(TemporalAmount amountToAdd) {
    FakeTime.offsetRealBy(amountToAdd);
  }

  default void restoreRealTime() {
    FakeTime.restoreReal();
  }
}
