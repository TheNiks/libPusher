//
//  SpecHelper.h
//  libPusher
//
//  Created by Luke Redpath on 13/12/2011.
//  Copyright (c) 2011 LJR Software Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Kiwi.h"
#import "PTPusher.h"
#import "PTPusherEvent.h"

#define kUSE_ENCRYPTED_CONNECTION YES

// helper methods

PTPusher *newTestClient(void);
void enableClientDebugging(void);
void sendTestEvent(NSString *eventName);
void sendTestEventOnChannel(NSString *channelName, NSString *eventName);
void onConnect(dispatch_block_t);
void onAuthorizationRequired(void (^authBlock)(NSMutableURLRequest *));
void onFailedToSubscribe(void (^failedToSubscribeBlock)(PTPusherChannel *));
void onSubscribe(void (^subscribeBlock)(PTPusherChannel *));
void waitForClientToDisconnect(PTPusher *client);

// helper classes

@interface PTPusherEventMatcher : KWMatcher {
  NSString *expectedEventName;
}
- (void)beEventNamed:(NSString *)name;
@end

@interface PTPusherClientTestHelperDelegate : NSObject <PTPusherDelegate> {
  BOOL connected;
  dispatch_block_t connectedBlock;
  void (^onAuthorizationBlock)(NSMutableURLRequest *);
  void (^onFailedToSubscribeBlock)(PTPusherChannel *);
  void (^onSubscribeBlock)(PTPusherChannel *);
}
@property (nonatomic, assign) BOOL debugEnabled;

+ (id)sharedInstance;
- (void)onConnect:(dispatch_block_t)block;
- (void)onAuthorizationRequired:(void (^)(NSMutableURLRequest *))authBlock;
- (void)onFailedToSubscribe:(void (^)(PTPusherChannel *))failedToSubscribeBlock;
- (void)onSubscribe:(void (^)(PTPusherChannel *))subscribeBlock;
@end

@interface PTPusherNotificationHandler : NSObject {
  NSMutableDictionary *observers;
}
@end

@interface NSNotificationCenter (BlockHandler)
- (void)addObserver:(NSString *)noteName object:(id)object usingBlock:(void (^)(NSNotification *))block;
@end
