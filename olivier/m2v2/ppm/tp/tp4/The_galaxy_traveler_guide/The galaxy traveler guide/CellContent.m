//
//  CellContent.m
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "CellContent.h"
#import "AppDelegate.h"

@implementation CellContent

-(id)initWithLabel:(NSString *) l andWithBool:(BOOL) b andPlanetNumber:(int) i {
    self = [self init];
    [self setLabel:l];
    
    UIImage *img;
    if (isJedi) {
        img = [UIImage imageNamed:@"leia.png"];
    } else {
        img = [UIImage imageNamed:@"vador.png"];
    }
    [self setImg:img];
    
    NSString *strAcces ;
  
    /*if (isJedi) {
        if (b) {
            strAcces = @"Has acces";
        } else {
            strAcces = @"Has not acces";
        }
    } else {
        if (!b){
        strAcces = @"Has acces";
        } else {
        strAcces = @"Has not acces";
        }

    }*/
    [self setHasAcces:strAcces];
    return self;
}

-(void) dealloc {
    [_label release];
    _label = nil;
    [_img release];
    _img = nil;
    [_hasAcces release];
    _hasAcces = nil;
    [super dealloc];
}


@end
