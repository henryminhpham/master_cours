//
//  ViewController.m
//  MiniNav
//
//  Created by m2sar on 02/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    view = [[View alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [[self view] addSubview:view];
}

-(BOOL) shouldAutorotate{
    return YES;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)o
                                duration:(NSTimeInterval)duration{
    [view setFromOrientation:o];
}

- (void) didRotateToInterfaceOrientation:(UIInterfaceOrientation)o{
    [view setFromOrientation:o];
}

@end
