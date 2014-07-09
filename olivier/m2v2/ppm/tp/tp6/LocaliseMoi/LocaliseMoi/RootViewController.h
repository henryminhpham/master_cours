//
//  RootViewController.h
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MapViewController.h"


@interface RootViewController : UITableViewController<UISplitViewControllerDelegate, UITabBarControllerDelegate> {
    
    NSMutableArray* historique;
    NSString* path;
}

@property(readwrite, nonatomic, retain) MapViewController* mapView;

@end
