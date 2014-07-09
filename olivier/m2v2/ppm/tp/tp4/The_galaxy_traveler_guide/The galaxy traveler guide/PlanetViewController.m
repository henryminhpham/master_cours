//
//  PlanetViewController.m
//  The galaxy traveler guide
//
//  Created by m2sar on 11/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "PlanetViewController.h"

@interface PlanetViewController ()

@end

@implementation PlanetViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        v = [[PlanetView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        [v setNumPlanet:self.numPlanet];
       
        [self setView:v];
        [v setBackgroundColor:[UIColor whiteColor]];
        navController = [super navigationController];
        [v setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    }
    return self;
}
- (id) initWithNum:(int) n{
    self = [super init];
    if (self) {
        [self setNumPlanet:n];
        v = [[PlanetView alloc] initWithFrame:[[UIScreen mainScreen] bounds] andWithNum: n];
        [v setNumPlanet:self.numPlanet];
        
        [self setView:v];
        [v setBackgroundColor:[UIColor whiteColor]];
        navController = [super navigationController];
        [v setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    }
    return self;
}

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

@end
