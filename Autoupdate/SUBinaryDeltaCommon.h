//
//  SUBinaryDeltaCommon.h
//  Sparkle
//
//  Created by Mark Rowe on 2009-06-01.
//  Copyright 2009 Mark Rowe. All rights reserved.
//

#ifndef SUBINARYDELTACOMMON_H
#define SUBINARYDELTACOMMON_H

#import <Foundation/Foundation.h>

#include <fts.h>

#define PERMISSION_FLAGS (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX)

#define IS_VALID_PERMISSIONS(mode) \
    (((mode & PERMISSION_FLAGS) == 0755) || ((mode & PERMISSION_FLAGS) == 0644))

#define APPLE_CODE_SIGN_XATTR_CODE_DIRECTORY_KEY "com.apple.cs.CodeDirectory"
#define APPLE_CODE_SIGN_XATTR_CODE_REQUIREMENTS_KEY "com.apple.cs.CodeRequirements"
#define APPLE_CODE_SIGN_XATTR_CODE_SIGNATURE_KEY "com.apple.cs.CodeSignature"

#define VERBOSE_DELETED "Deleted" // file is deleted from the file system when applying a patch
#define VERBOSE_REMOVED "Removed" // file is set to be removed when creating a patch
#define VERBOSE_ADDED "Added" // file is added to the patch or file system
#define VERBOSE_DIFFED "Diffed" // file is diffed when creating a patch
#define VERBOSE_PATCHED "Patched" // file is patched when applying a patch
#define VERBOSE_UPDATED "Updated" // file's contents are updated
#define VERBOSE_MODIFIED "Modified" // file's metadata is modified

#define MAJOR_VERSION_IS_AT_LEAST(actualMajor, expectedMajor) (actualMajor >= expectedMajor)

// Each major version will be assigned a name of a color
// Changes that break backwards compatibility will have different major versions
// Changes that affect creating but not applying patches will have different minor versions

typedef NS_ENUM(uint16_t, SUBinaryDeltaMajorVersion)
{
    // Note: support for creating or applying version 1 deltas have been removed
    SUBinaryDeltaMajorVersion1 = 1,
    SUBinaryDeltaMajorVersion2 = 2
};

#define FIRST_DELTA_DIFF_MAJOR_VERSION SUBinaryDeltaMajorVersion1
#define FIRST_SUPPORTED_DELTA_MAJOR_VERSION SUBinaryDeltaMajorVersion2
#define LATEST_DELTA_DIFF_MAJOR_VERSION SUBinaryDeltaMajorVersion2

extern int compareFiles(const FTSENT **a, const FTSENT **b);
extern NSString *hashOfTreeWithVersion(NSString *path, uint16_t majorVersion);
extern NSString *hashOfTree(NSString *path);
extern BOOL removeTree(NSString *path);
extern BOOL copyTree(NSString *source, NSString *dest);
extern BOOL modifyPermissions(NSString *path, mode_t desiredPermissions);
extern NSString *pathRelativeToDirectory(NSString *directory, NSString *path);
NSString *temporaryFilename(NSString *base);
NSString *temporaryDirectory(NSString *base);
NSString *stringWithFileSystemRepresentation(const char*);
uint16_t latestMinorVersionForMajorVersion(SUBinaryDeltaMajorVersion majorVersion);
#endif
