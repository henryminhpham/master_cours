//
//  MyCell.m
//  iMoods
//
//  Created by m2sar on 12/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "MyCell.h"

@implementation MyCell

-(id)initWithLabel:(NSString *)l andWithDetail:(NSString *)d {
    self = [self init];
    [self setLabel:l];
    [self setDetail:d];    
    return self;
}


-(void)dealloc{
    [_label release];
    _label = nil;
    [_detail release];
    _detail = nil;
    [super dealloc];
}

@end
