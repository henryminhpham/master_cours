//
//  PlanetView.h
//  The galaxy traveler guide
//
//  Created by m2sar on 11/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "PlanetViewController.h"

@interface PlanetView : UIView {
    UIImageView *img;
    UIImageView *bg;
    UILabel *label;
    CGRect myframe;
    NSArray *tabNom;
    BOOL isIpad;
    int xOrig, yOrig, rapport, heigth, width;

}
-(void) setFromOrientation:(UIInterfaceOrientation) o;
@property(readwrite,nonatomic,assign) int numPlanet;
@end
