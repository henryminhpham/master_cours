//
//  PlanetView.m
//  The galaxy traveler guide
//
//  Created by m2sar on 11/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "PlanetView.h"
//#import "PlanetViewController.h"

@implementation PlanetView

- (id)initWithFrame:(CGRect)frame  andWithNum:(int) n
{
    tabNom = [[NSArray alloc] initWithObjects:@"Tatooine",@"Yavin IV",@"Endor",@"Geonosis",@"Hoth",@"Coruscan",@"Alderaan",@"Bespin",@"Kamino",@"Mustafar",@"Dagobah",@"Dantooine",@"Bestine",@"Polus",@"Mon Calamari",@"Kuath",@"Sholah",@"Ryloth",@"Alzoc III",@"Jabin", nil];
    [self setNumPlanet:n];
    
    self = [super initWithFrame:frame];
    myframe = frame;
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        isIpad = NO;
    } else {
        isIpad = YES;
    }
    if (self) {
        bg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"chatelet-elements/fond-2048x2048.jpg"]];
        [self addSubview:bg];
        [bg release];
        
        if (isIpad) {
            xOrig = 20;
            yOrig = 20;
            rapport = 2;
        } else {
            xOrig = 10;
            yOrig = 10;
            rapport = 1;
        }
    
        img = [[UIImageView alloc ] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"chatelet-elements/planete-%d.png",self.numPlanet]]];
        [self addSubview:img];
        [img release];
        
        label = [[UILabel alloc] init];
        [label setText:[NSString stringWithFormat:@"%@",[tabNom objectAtIndex:self.numPlanet]]];
         [self addSubview:label];
         [label release];
    }
    return self;
}



-(void) setFromOrientation:(UIInterfaceOrientation) o{
    
    
    if (o == UIInterfaceOrientationLandscapeLeft ||
        o == UIInterfaceOrientationLandscapeRight) {
        
        heigth = myframe.size.width;
        width = myframe.size.height;
        
        [label setFrame:CGRectMake(xOrig, yOrig+50, width, 50)];
        [label setTextAlignment:NSTextAlignmentCenter];
        [img setFrame:CGRectMake(xOrig, 2*yOrig+100, width-2*xOrig, width-2*xOrig)];
        
        
    }
    else {
        width = myframe.size.width;
        heigth = myframe.size.height;
        
        [label setFrame:CGRectMake(xOrig, yOrig+50, width, 50)];
        [label setTextAlignment:NSTextAlignmentCenter];
        [img setFrame:CGRectMake(xOrig, 2*yOrig+100, width-2*xOrig, width-2*xOrig)];
        
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
