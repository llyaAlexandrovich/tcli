#pragma once



#include <iostream>
#include <string>
#include <string_view>






/**
 * Convert the string representation of the version to an integer representation.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param StringVersion  string representation of the version
 * 
 * @return integer representation of the given version
 * 
 * @since 1.0.0
 */
[[nodiscard]] int CalculateVersion(std::string StringVersion) noexcept;



/**
 * Get major number of the version from the string version representation.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param StringVersion  string representation of the version
 * 
 * @return number that represents the major part of the version
 * 
 * @since 1.0.0
 */
[[nodiscard]] int GetMajorVersion(std::string StringVersion) noexcept;



/**
 * Get minor number of the version from the string version representation.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param StringVersion  string representation of the version
 * 
 * @return number that represents the minor part of the version
 * 
 * @since 1.0.0
 */
[[nodiscard]] int GetMinorVersion(std::string StringVersion) noexcept;



/**
 * Get patch number of the version from the string version representation.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param StringVersion  string representation of the version
 * 
 * @return number that represents the patch part of the version
 * 
 * @since 1.0.0
 */
[[nodiscard]] int GetPatchVersion(std::string StringVersion) noexcept;



/**
 * Validate language-code typically given by the user to the **argv.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param locale  user-provided language code to verify
 * 
 * @return return whether true if locale exists or false
 * 
 * @since 1.0.0
 */
[[nodiscard]] bool ValidateLanguageCode(std::string& locale) noexcept;
