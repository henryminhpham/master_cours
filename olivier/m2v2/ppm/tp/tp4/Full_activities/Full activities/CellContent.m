//
//  CellContent.m
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "CellContent.h"

@implementation CellContent

-(id)initWithLabel:(NSString *)l andWithDetail:(NSString *)d andWithPrio:(int)p{
    self = [self init];
    [self setLabel:l];
    [self setDetail:d];
    
    UIImage *img = [UIImage imageNamed:[NSString stringWithFormat:@"fullactivities-elements/prio%d.png",p]];
    [self setPastille:img];
    
    return self;
}


-(void)dealloc{
    [_label release];
    _label = nil;
    [_detail release];
    _detail = nil;
    [_pastille release];
    _pastille = nil;
    
    [super dealloc];
}
@end
