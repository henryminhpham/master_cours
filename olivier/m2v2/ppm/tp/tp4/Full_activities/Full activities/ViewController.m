//
//  ViewController.m
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	myTVC = [[TableViewController alloc] initWithStyle:UITableViewStyleGrouped];
    
    [myTVC setTitle:@"TO-DO List"];
    
    navController = [[UINavigationController alloc] initWithRootViewController:myTVC];
    
    UIView *mainView = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [mainView addSubview:[navController view]];
    [mainView addSubview:[myTVC view]];
    [self setView:mainView];
    [mainView release];
    
    [[myTVC tableView] setDelegate:myTVC];
    [[myTVC tableView] setDataSource:myTVC];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)dealloc{
    [myTVC release];
    myTVC = nil;
    [super dealloc];
}

@end
