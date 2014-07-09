//
//  MoodControllerViewController.h
//  iMoods
//
//  Created by m2sar on 12/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MyCell.h"
#import "SecondViewController.h"

@interface MyTableViewController : UITableViewController<UITableViewDataSource, UITableViewDelegate, NSNetServiceBrowserDelegate, NSNetServiceDelegate> {
    
    NSMutableArray* voisins;
    NSNotificationCenter* center;
    NSNetService* find;
    NSNetServiceBrowser* findBrowser;
    NSString* currentMood;
    NSMutableArray* services;
}

- (void) publish;

@end
