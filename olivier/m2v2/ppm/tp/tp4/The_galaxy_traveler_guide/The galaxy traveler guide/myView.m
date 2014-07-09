//
//  myView.m
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "myView.h"
#import "AppDelegate.h"

@implementation myView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    self = [super initWithFrame:frame];
    myframe = frame;
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        isIpad = NO;
    } else {
        isIpad = YES;
    }
    if (self) {
        bg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"chatelet-elements/fond-2048x2048.jpg"]];
        [self addSubview:bg];
        [bg release];
        
        if (isIpad) {
            xOrig = 20;
            yOrig = 20;
            rapport = 2;
        } else {
            xOrig = 10;
            yOrig = 10;
            rapport = 1;
        }
        tab = [[NSArray alloc] initWithObjects:@"", @"", nil];
        
        //heigth = myframe.size.height;
        //width = myframe.size.width;
        
        
        
               
        select = [[UISegmentedControl alloc] initWithItems:tab];
        [select setBackgroundImage:[UIImage imageNamed:@"chatelet-elements/back-segmented.png"] forState:UIControlStateNormal barMetrics:UIBarMetricsDefault];
        [select setDividerImage:[UIImage imageNamed:@"chatelet-elements/div-segmented.png"] forLeftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateNormal barMetrics:UIBarMetricsDefault];
        [select setSelectedSegmentIndex:0];
        [select addTarget:self action:@selector(setJedi) forControlEvents:UIControlEventAllEvents];
        //[select setFrame:CGRectMake(width/2-100, heigth/2-35, 200, 70)];
        [self addSubview:select];
        [select release];
        
    }
    return self;
}


-(void) setJedi{
   
    if ([select selectedSegmentIndex] ==0) {
        isJedi = YES;
         NSLog(@"set jedi : %hhdd",isJedi);
    } else {
        isJedi = NO;
         NSLog(@"set jedi : %hhdd",isJedi);
    }
}

-(void) setFromOrientation:(UIInterfaceOrientation) o{
    
    if (o == UIInterfaceOrientationLandscapeLeft ||
        o == UIInterfaceOrientationLandscapeRight) {
        
        heigth = myframe.size.width;
        width = myframe.size.height;
        
        [select setFrame:CGRectMake(width/2-100, heigth/2-35, 200, 70)];
    }
    else {
        width = myframe.size.width;
        heigth = myframe.size.height;
        
        [select setFrame:CGRectMake(width/2-100, heigth/2-35, 200, 70)];
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
