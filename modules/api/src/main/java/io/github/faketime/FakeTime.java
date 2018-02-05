package io.github.faketime;

import static java.time.temporal.ChronoUnit.SECONDS;

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.OffsetDateTime;
import java.time.ZoneId;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;
import java.time.temporal.TemporalAmount;

public class FakeTime {

  private static final String ABSOLUTE_PROPERTY = "faketime.absolute.ms";
  private static final String OFFSET_PROPERTY = "faketime.offset.ms";

  public static void stopAt(long epochMillisecond) {
    restoreReal();
    System.setProperty(ABSOLUTE_PROPERTY, Long.toString(epochMillisecond));
  }

  public static void stopAt(Instant instant) {
    stopAt(instant.getEpochSecond() * 1_000 + instant.getNano() / 1_000_000);
  }

  public static void stopAt(ZonedDateTime zonedDateTime) {
    stopAt(zonedDateTime.toInstant());
  }

  public static void stopAt(OffsetDateTime offsetDateTime) {
    stopAt(offsetDateTime.toInstant());
  }

  public static void stopAt(LocalDateTime localDateTime) {
    stopAt(localDateTime.atZone(ZoneOffset.systemDefault()));
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, int minute, int second, int millisecond, ZoneId zone) {
    stopAt(ZonedDateTime.of(year, month, dayOfMonth, hour, minute, second, millisecond * 1_000_000, zone));
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, int minute, int second, ZoneId zone) {
    stopAt(year, month, dayOfMonth, hour, minute, second, 0, zone);
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, int minute, ZoneId zone) {
    stopAt(year, month, dayOfMonth, hour, minute, 0, zone);
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, ZoneId zone) {
    stopAt(year, month, dayOfMonth, hour, 0, zone);
  }

  public static void stopAt(int year, int month, int dayOfMonth, ZoneId zone) {
    stopAt(year, month, dayOfMonth, 0, zone);
  }

  public static void stopAtUtc(int year, int month, int dayOfMonth, int hour, int minute, int second, int millisecond) {
    stopAt(year, month, dayOfMonth, hour, minute, second, millisecond, ZoneOffset.UTC);
  }

  public static void stopAtUtc(int year, int month, int dayOfMonth, int hour, int minute, int second) {
    stopAtUtc(year, month, dayOfMonth, hour, minute, second, 0);
  }

  public static void stopAtUtc(int year, int month, int dayOfMonth, int hour, int minute) {
    stopAtUtc(year, month, dayOfMonth, hour, minute, 0);
  }

  public static void stopAtUtc(int year, int month, int dayOfMonth, int hour) {
    stopAtUtc(year, month, dayOfMonth, hour, 0);
  }

  public static void stopAtUtc(int year, int month, int dayOfMonth) {
    stopAtUtc(year, month, dayOfMonth, 0);
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, int minute, int second, int millisecond) {
    stopAt(year, month, dayOfMonth, hour, minute, second, millisecond, ZoneOffset.systemDefault());
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, int minute, int second) {
    stopAt(year, month, dayOfMonth, hour, minute, second, 0);
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour, int minute) {
    stopAt(year, month, dayOfMonth, hour, minute, 0);
  }

  public static void stopAt(int year, int month, int dayOfMonth, int hour) {
    stopAt(year, month, dayOfMonth, hour, 0);
  }

  public static void stopAt(int year, int month, int dayOfMonth) {
    stopAt(year, month, dayOfMonth, 0);
  }

  public static void offsetStoppedBy(long milliseconds) {
    stopAt(System.currentTimeMillis() + milliseconds);
  }

  public static void offsetStoppedBySeconds(long seconds) {
    stopAt(LocalDateTime.now().plusSeconds(seconds));
  }

  public static void offsetStoppedByMinutes(long minutes) {
    stopAt(LocalDateTime.now().plusMinutes(minutes));
  }

  public static void offsetStoppedByHours(long hours) {
    stopAt(LocalDateTime.now().plusHours(hours));
  }

  public static void offsetStoppedByDays(long days) {
    stopAt(LocalDateTime.now().plusDays(days));
  }

  public static void offsetStoppedBy(TemporalAmount amountToAdd) {
    stopAt(LocalDateTime.now().plus(amountToAdd));
  }

  public static void offsetBy(long milliseconds) {
    restoreReal();
    System.setProperty(OFFSET_PROPERTY, Long.toString(milliseconds));
  }

  public static void offsetBySeconds(int seconds) {
    offsetBy(seconds * 1_000);
  }

  public static void offsetByMinutes(int minutes) {
    offsetBySeconds(minutes * 60);
  }

  public static void offsetByHours(int hours) {
    offsetByMinutes(hours * 60);
  }

  public static void offsetByDays(int days) {
    offsetByHours(days * 24);
  }

  public static void offsetBy(TemporalAmount amountToAdd) {
    offsetBy(amountToAdd.get(SECONDS) * 1_000);
  }

  public static void restoreReal() {
    System.clearProperty(ABSOLUTE_PROPERTY);
    System.clearProperty(OFFSET_PROPERTY);
  }
}
