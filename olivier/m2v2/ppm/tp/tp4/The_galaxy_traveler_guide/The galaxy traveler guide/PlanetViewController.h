//
//  PlanetViewController.h
//  The galaxy traveler guide
//
//  Created by m2sar on 11/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "PlanetView.h"

@interface PlanetViewController : UIViewController {
   // PlanetView *v;
    UINavigationController *navController;
    PlanetView *v;
    
}
@property(readwrite,nonatomic,assign) int numPlanet;
@end
