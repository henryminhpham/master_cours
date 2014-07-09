//
//  TableViewController.h
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CellContent.h"

@interface TableViewController : UITableViewController<UITableViewDelegate, UITableViewDataSource>{
    int compteur;
    NSMutableArray *content;
}

@end
