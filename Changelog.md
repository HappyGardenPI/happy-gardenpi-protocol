# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
 - Add updateIdToBufferEncoded() on vector of buffer
 - Add decode() for Buffer param
 - Add decodeFirst() for Buffers param
 - Add generateRandomString()
 - Add generateRandomUint8()
### Changed
 - Fix get version in getVersion()

## [2.1.0] - 2021-10-23
### Added
 - Add getVersion function
 - Add GCC 10 compatibility
 - Add composeDecodedChunks()
 - Add endCommunication()
 - Add test 
### Changed
 - inline namespace from v1 to v2
 - Fix updateIdToBufferEncoded()
### Removed
 - Remove v1 code
 - Removed vector type and defined new specific type
 
## [2.0.0] - 2021-10-10
### Added
 - Shared pointer management
### Changed
 - Change interface layout
 - Fix memory leak
 - Fix chunk package usage
 - Fix error in package
 - Fix test
### Removed
 - Remove back compatibility

## [1.0.1] - 2021-08-23
### Changed
 - Change memory management 

## [1.0.0] - 2021-08-22
### Added
 - First release 
 
[2.0.0]: https://github.com/HappyGardenPI/happy-gardenpi-protocol/releases/tag/v2.0.0
[1.0.1]: https://github.com/HappyGardenPI/happy-gardenpi-protocol/releases/tag/v1.0.1
[1.0.0]: https://github.com/HappyGardenPI/happy-gardenpi-protocol/releases/tag/v1.0.0
What is a changelog?
A changelog is a file which contains a curated, chronologically ordered list o