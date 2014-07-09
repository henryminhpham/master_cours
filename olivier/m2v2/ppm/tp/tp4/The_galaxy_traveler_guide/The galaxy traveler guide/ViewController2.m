//
//  ViewController2.m
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "ViewController2.h"

@interface ViewController2 ()

@end

@implementation ViewController2



- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    if (self) {
        
        myTVC = [[TableViewController alloc] initWithStyle:UITableViewStylePlain];
        
        navController = [[UINavigationController alloc] initWithRootViewController:myTVC];

        [myTVC setTitle:@"My planets"];
        UIView *mainView = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        [mainView addSubview:[myTVC view]];
        [mainView addSubview:[navController view]];
        [self setView:mainView];
        [mainView release];
        
        [[myTVC tableView] setDelegate:myTVC];
        [[myTVC tableView] setDataSource:myTVC];
        
        UITabBarItem * tbi = [[UITabBarItem alloc]initWithTabBarSystemItem:UITabBarSystemItemBookmarks tag:1];
        [self setTabBarItem:tbi];
    }
    
    return self;
}



- (void) dealloc{
    [myTVC release];
    myTVC = nil;
    [navController release];
    navController = nil;
    [super dealloc];
}

@end
