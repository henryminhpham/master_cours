//
//  myView.h
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface myView : UIView {
    UISegmentedControl *select;
    UIView *bg;
    
    NSArray *tab;
    
    CGRect myframe;
    
    int xOrig, yOrig, width, heigth, rapport;
    BOOL isIpad;
}

-(void) setFromOrientation:(UIInterfaceOrientation) o;

@end
