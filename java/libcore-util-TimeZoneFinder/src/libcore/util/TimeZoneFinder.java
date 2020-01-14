/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package libcore.util;

import java.io.IOException;
import java.util.List;
import android.icu.util.TimeZone;

import libcore.timezone.CountryZonesFinder;
import libcore.timezone.CountryTimeZones;

/**
 * A class that can find matching time zones by loading data from the tzlookup.xml file.
 * @hide
 */
public class TimeZoneFinder {
    private static libcore.timezone.TimeZoneFinder zfInternal;
    private static TimeZoneFinder instance;

    public TimeZoneFinder() {
        zfInternal = libcore.timezone.TimeZoneFinder.getInstance();
    }

    public static synchronized TimeZoneFinder getInstance( ) {
        if (instance == null)
            instance=new TimeZoneFinder();
        return instance;
    }

    /**
     * Parses the data file, throws an exception if it is invalid or cannot be read.
     */
    public void validate() throws IOException {
        zfInternal.validate();
    }

    /**
     * Returns the IANA rules version associated with the data. If there is no version information
     * or there is a problem reading the file then {@code null} is returned.
     */
    public String getIanaVersion() {
        return zfInternal.getIanaVersion();
    }

    /**
     * Loads all the country &lt;-&gt; time zone mapping data into memory. This method can return
     * {@code null} in the event of an error while reading the underlying data files.
     */
    public CountryZonesFinder getCountryZonesFinder() {
        return zfInternal.getCountryZonesFinder();
    }

    /**
     * Returns a frozen ICU time zone that has / would have had the specified offset and DST value
     * at the specified moment in the specified country.
     *
     * <p>In order to be considered a configured zone must match the supplied offset information.
     *
     * <p>Matches are considered in a well-defined order. If multiple zones match and one of them
     * also matches the (optional) bias parameter then the bias time zone will be returned.
     * Otherwise the first match found is returned.
     */
    public TimeZone lookupTimeZoneByCountryAndOffset(
            String countryIso, int offsetMillis, boolean isDst, long whenMillis, TimeZone bias) {
        return zfInternal.lookupTimeZoneByCountryAndOffset(countryIso, offsetMillis, isDst, whenMillis, bias);
    }

    /**
     * Returns a "default" time zone ID known to be used in the specified country. This is
     * the time zone ID that can be used if only the country code is known and can be presumed to be
     * the "best" choice in the absence of other information. For countries with more than one zone
     * the time zone will not be correct for everybody.
     *
     * <p>If the country code is not recognized or there is an error during lookup this can return
     * null.
     */
    public String lookupDefaultTimeZoneIdByCountry(String countryIso) {
        return zfInternal.lookupDefaultTimeZoneIdByCountry(countryIso);
    }

    /**
     * Returns an immutable list of frozen ICU time zones known to be used in the specified country.
     * If the country code is not recognized or there is an error during lookup this can return
     * null. The TimeZones returned will never contain {@link TimeZone#UNKNOWN_ZONE}. This method
     * can return an empty list in a case when the underlying data files reference only unknown
     * zone IDs.
     */
    public List<TimeZone> lookupTimeZonesByCountry(String countryIso) {
        return zfInternal.lookupTimeZonesByCountry(countryIso);
    }

    /**
     * Returns an immutable list of time zone IDs known to be used in the specified country.
     * If the country code is not recognized or there is an error during lookup this can return
     * null. The IDs returned will all be valid for use with
     * {@link java.util.TimeZone#getTimeZone(String)} and
     * {@link android.icu.util.TimeZone#getTimeZone(String)}. This method can return an empty list
     * in a case when the underlying data files reference only unknown zone IDs.
     */
    public List<String> lookupTimeZoneIdsByCountry(String countryIso) {
        return zfInternal.lookupTimeZoneIdsByCountry(countryIso);
    }

    /**
     * Returns a {@link CountryTimeZones} object associated with the specified country code.
     * Caching is handled as needed. If the country code is not recognized or there is an error
     * during lookup this method can return null.
     */
    public CountryTimeZones lookupCountryTimeZones(String countryIso) {
        return zfInternal.lookupCountryTimeZones(countryIso);
    }
}
