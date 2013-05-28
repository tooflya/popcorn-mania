/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#import "AppController.h"
#import "AppDelegate.h"

static AppDelegate s_sharedApplication;

@implementation AppController

	@synthesize window, glView;

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
		NSRect rect = NSMakeRect(0, 0, 1136, 640);
		window = [[NSWindow alloc] initWithContentRect:rect
			styleMask:( NSClosableWindowMask | NSTitledWindowMask )
			backing:NSBackingStoreBuffered
			defer:YES];
		
		glView = [[EAGLView alloc] initWithFrame:rect];

		[window becomeFirstResponder];
		[window setContentView:glView];
		[window setTitle:@"Popcorn Mania"];
		[window makeKeyAndOrderFront:self];
		[window setAcceptsMouseMovedEvents:YES];

		cocos2d::CCApplication::sharedApplication()->run();
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
		return YES;
	}

	-(void) dealloc
	{
		cocos2d::CCDirector::sharedDirector()->end();
		[super dealloc];
	}

#pragma mark -
#pragma mark IB Actions

	-(IBAction) toggleFullScreen:(id)sender
	{
		EAGLView* pView = [EAGLView sharedEGLView];
		[pView setFullScreen:!pView.isFullScreen];
	}

	-(IBAction) exitFullScreen:(id)sender
	{
		[[EAGLView sharedEGLView] setFullScreen:NO];
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MPMoviePlayerViewController *playerViewController=NULL;
int g_iPlayVideoState=0;

- (void)PlayVideo:(int)iStateAfterPlay fullscreen:(int)iFullScreen file:(NSString*)strFilennameNoExtension fileExtension:(NSString*)strExtension
{
    NSLog(@"PlayVideo start");
    
    g_iPlayVideoState = 2;
    
    NSString *url = [[NSBundle mainBundle] pathForResource:strFilennameNoExtension ofType:strExtension];
    
    CGRect rScreen;
    rScreen.origin.x = 0;
    rScreen.origin.y = 0;
    rScreen.size.width = 480;
    rScreen.size.height = 320;
    //rScreen = CGRect::CGRectMake(0,0, 480, 320);
    
    id anid;
    if( iFullScreen==0 )
    {
        MPMoviePlayerController *player2 = [[MPMoviePlayerController alloc]
                                            initWithContentURL:[NSURL fileURLWithPath:url]];
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(movieFinishedCallback:)
         name:MPMoviePlayerPlaybackDidFinishNotification
         object:player2];
        
        //---play partial screen---
        player2.view.frame = rScreen;
        //    player2.view.frame = CGRectMake(0,0, m_iScreenWidth, m_iScreenHeight);
        anid = [self addSubview:player2.view];
        player2.shouldAutoplay=TRUE;
        //---play movie---
        [player2 play];
    }
    else
    {
        playerViewController = [[MPMoviePlayerViewController alloc]
                                initWithContentURL:[NSURL fileURLWithPath:url]];
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(movieFinishedCallback:)
         name:MPMoviePlayerPlaybackDidFinishNotification
         object:[playerViewController moviePlayer]];
        
        playerViewController.view.frame = rScreen;
        
        cocos2d::CCDirector::sharedDirector()->purgeCachedData();
        
        // Add the view - Use this one line for Cocos2D Obj C
        //cocos2d::CCDirector::sharedDirector()->openGLView->addSubview(playerViewController.view);
        
        //        playerViewController.view = [[UIView alloc]initWithFrame : rScreen];
        //        [playerViewController.view setBackgroundColor: [UIColor clearColor]];
        //    playerViewController.view.frame = rScreen;
        //[playerViewController.view setCenter: 0];
        //[super setPosition: 0];
        
        EAGLView *view = [EAGLView sharedEGLView];
        [view addSubview:playerViewController.view];
        
        //[viewController.view  addSubview:moviePlayer.view];
        [view sendSubviewToBack:view];
        
        NSLog(@"pView inserted");
        
        // Add the view - Use these three lines for Cocos 2D X
        window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
        [window addSubview: playerViewController.view];
        [window makeKeyAndVisible];
        
        //---play movie---
        MPMoviePlayerController *player = [playerViewController moviePlayer];
        player.scalingMode=MPMovieScalingModeAspectFit;
        player.shouldAutoplay=TRUE;
        [player play];
        
    }
    
    g_iPlayVideoState = 1;
    
    NSLog(@"PlayVideo done");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (void) movieFinishedCallback:(NSNotification*) aNotification
{
    NSLog(@"movieFinishedCallback");
    MPMoviePlayerController *player = [aNotification object];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:player];
    
    [player.view removeFromSuperview];
    g_iPlayVideoState = 0;
    [window setHidden:true];
    [playerViewController release];
    
    NSLog(@"movieFinishedCallback done");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


@end
