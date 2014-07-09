//
//  ViewController.m
//  tp1exo1
//
//  Created by m2sar on 23/11/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

bool show = false;

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

- (IBAction)buttonAction:(UIButton *)sender {
    if(show) {
        [_label setText:@"AuRevoir"];
        [_button setTitle:@"DisBonjour" forState:UIControlStateNormal];
    } else {
        [_label setText:@"Bonjour"];
        [_button setTitle:@"DisAuRevoir" forState:UIControlStateNormal];
    }
    show = !show;
}
@end
