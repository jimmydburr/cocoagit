//
//  GITServerHandler.h
//  CocoaGit
//
//  Created by Scott Chacon on 1/3/09.
//  Copyright 2009 GitHub. All rights reserved.
//

#include <CommonCrypto/CommonDigest.h>
#import "GITRepo.h"
#import "GITObject.h"
#import "GITSocket.h"

@interface GITServerHandler : NSObject {
	NSString *workingDir;

	GITSocket	*gitSocket;
	GITRepo		*gitRepo;
	NSString	*gitPath;

	NSMutableArray *refsRead;
	NSMutableArray *needRefs;
	NSMutableDictionary *refDict;
	
	int	capabilitiesSent; // Why not use a BOOL here?
}

@property(copy, readwrite) NSString *workingDir;

@property(retain, readwrite) GITSocket	*gitSocket;
@property(retain, readwrite) GITRepo	*gitRepo;
@property(retain, readwrite) NSString	*gitPath;

@property(copy, readwrite) NSMutableArray *refsRead;
@property(copy, readwrite) NSMutableArray *needRefs;
@property(copy, readwrite) NSMutableDictionary *refDict;

@property(assign, readwrite) int capabilitiesSent;


- (void) initWithGit:(GITRepo *)git gitPath:(NSString *)gitRepoPath withSocket:(GITSocket *)gSocket;
- (void) handleRequest;

- (void) uploadPack:(NSString *)repositoryName;
- (void) receiveNeeds;
- (void) uploadPackFile;
- (void) sendPackData;

- (void) receivePack:(NSString *)repositoryName;
- (void) gatherObjectShasFromCommit:(NSString *)shaValue;
- (void) gatherObjectShasFromTree:(NSString *)shaValue;
- (void) respondPack:(uint8_t *)buffer length:(int)size checkSum:(CC_SHA1_CTX *)checksum;

- (void) sendNack;

- (void) sendRefs;
- (void) sendRef:(NSString *)refName sha:(NSString *)shaString;
- (void) readRefs;
- (void) readPack;
- (void) writeRefs;
- (NSData *) readData:(int)size;
- (NSString *) typeString:(int)type;
- (int) typeInt:(NSString *)type;
- (void) unpackDeltified:(int)type size:(int)size;

- (NSData *) patchDelta:(NSData *)deltaData withObject:(GITObject *)gitObject;
- (NSArray *) patchDeltaHeaderSize:(NSData *)deltaData position:(unsigned long)position;

- (NSString *)readServerSha;
- (int) readPackHeader;
- (void) unpackObject;

- (void) longVal:(uint32_t)raw toByteBuffer:(uint8_t *)buffer;

@end
