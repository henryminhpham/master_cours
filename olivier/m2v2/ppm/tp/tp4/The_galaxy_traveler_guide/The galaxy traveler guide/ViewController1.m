//
//  ViewController.m
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "ViewController1.h"

@interface ViewController1 ()

@end

@implementation ViewController1

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    if (self) {
        v = [[myView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        [self setView:v];
        [v setBackgroundColor:[UIColor whiteColor]];
        UITabBarItem * tbi = [[UITabBarItem alloc]initWithTabBarSystemItem:UITabBarSystemItemContacts tag:1];
        [self setTabBarItem:tbi];
        
        [v setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    }
    
    return self;
}

-(void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)o
                                duration:(NSTimeInterval)duration{
    [v setFromOrientation:o];
}

- (void) didRotateToInterfaceOrientation:(UIInterfaceOrientation)o{
    [v setFromOrientation:o];
}

@end
