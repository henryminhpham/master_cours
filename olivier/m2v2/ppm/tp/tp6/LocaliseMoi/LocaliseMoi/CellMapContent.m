//
//  CellMapContent.m
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "CellMapContent.h"

@implementation CellMapContent

@synthesize label;
@synthesize latitude;
@synthesize longitude;

- (id) init {
    return [super init];
}

- (void) encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeDouble:latitude forKey:@"latitude"];
    [aCoder encodeDouble:longitude forKey:@"longitude"];
    [aCoder encodeObject:label forKey:@"label"];
}

- (id) initWithCoder:(NSCoder *)aDecoder {
    latitude = [aDecoder decodeDoubleForKey:@"latitude"];
    longitude = [aDecoder decodeDoubleForKey:@"longitude"];
    label = [[aDecoder decodeObjectForKey:@"label"] retain];
    return self;
}

- (void) dealloc {
    if(label != nil)
        [label release];
    label = nil;
    [super dealloc];
}

- (NSString*) description {
    return [NSString stringWithFormat:@"%@ %f %f", label, latitude, longitude];
}

@end
