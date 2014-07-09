//
//  myCustomAnnotation.m
//  iSouvenir
//
//  Created by m2sar on 04/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "myCustomAnnotation.h"

@implementation myCustomAnnotation
@synthesize coordinate;

-(id) initWithLocation:(CLLocationCoordinate2D)coord{
    self = [super init];
    
    if (self) {
        coordinate = coord;
    }
}

-(void) dealloc{
    [super dealloc];
}

@end

