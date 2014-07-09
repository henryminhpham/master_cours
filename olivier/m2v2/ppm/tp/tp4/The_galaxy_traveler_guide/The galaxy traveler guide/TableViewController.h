//
//  TableViewController.h
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CellContent.h"
#import "PlanetViewController.h"

@interface TableViewController : UITableViewController {
    int compteur;
    NSMutableArray *content;
    UINavigationController *navController;
}

@end
