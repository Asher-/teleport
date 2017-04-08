//
//  TPLayoutHost.h
//  teleport
//
//  Created by JuL on Sun Feb 29 2004.
//  Copyright (c) 2003-2005 abyssoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TPLayoutView.h"

#define ROUND_RECT 1
#define FLIPPED_VIEW 0

#if ROUND_RECT
#define FORDRAW_ORIGIN(x) (round(x))
#define FORDRAW_SIZE(x) (round(x))
#else
#define FORDRAW_ORIGIN(x) (x)
#define FORDRAW_SIZE(x) (x)
#endif
#define MIN_SCALE 0.01
#define MAX_SCALE 0.2

typedef NS_ENUM(NSInteger, TPDrawMode) {NORMAL_MODE, DISABLED_MODE, SELECTED_MODE} ;

@class TPHost, TPLayoutHostView;

@interface NSBezierPath (TeleportAdditions)

+ (void)drawRect:(NSRect)rect withGradientFrom:(NSColor*_Nullable)colorStart to:(NSColor*_Nullable)colorEnd;

@end

@interface TPLayoutScreenView : NSView
{
	TPLayoutHostView * _hostView;
	unsigned _screenIndex;
}

- (instancetype _Nonnull )initWithFrame:(NSRect)frameRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *_Nullable)coder NS_DESIGNATED_INITIALIZER;
- (instancetype _Nullable ) initWithHostView:(TPLayoutHostView*_Nullable)hostView screenIndex:(unsigned)screenIndex NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) TPLayoutHostView * _Nullable hostView;
@property (nonatomic, readonly, strong) NSScreen * _Nullable screen;
@property (nonatomic, readonly) unsigned int screenIndex;
@property (nonatomic, getter=isMainScreen, readonly) BOOL mainScreen;

- (void)update;

- (void)drawHostTitleInRect:(NSRect)rect dimmed:(BOOL)dimmed;

@end

@interface TPLayoutHostView : NSView
{
	NSString * _hostIdentifier;
	TPLayoutView * _layoutView;
	NSPoint _origin;
	TPDrawMode drawMode;
}

//- (void)setRealFrame:(NSRect)frame;

+ (Class _Nullable )screenViewClass;

- (instancetype _Nonnull )initWithFrame:(NSRect)frameRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *_Nullable)coder NS_DESIGNATED_INITIALIZER;
- (instancetype _Nullable ) initWithHost:(TPHost*_Nullable)host layoutView:(TPLayoutView*_Nullable)layoutView NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSString * _Nullable hostIdentifier;
@property (nonatomic, readonly, strong) TPHost * _Nullable host;

@property (nonatomic, readonly) NSRect totalFrame;
@property (nonatomic, readonly, copy) NSArray * _Nullable screenViews;
- (unsigned)indexOfScreenAtPoint:(NSPoint)point;
- (TPLayoutScreenView*_Nullable)screenViewAtIndex:(unsigned)index;
- (NSRect)screenFrameAtIndex:(unsigned)index;
- (NSRect)hostFrameFromScreenFrame:(NSRect)frame atIndex:(unsigned)index;

- (void)updateLayoutWithScaleFactor:(float)scaleFactor;

#if 0
- (void)setDrawMode:(TPDrawMode)drawMode;
- (void)setOrigin:(NSPoint)origin;
#endif

@end
