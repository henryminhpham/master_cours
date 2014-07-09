//
//  MyCell.h
//  iMoods
//
//  Created by m2sar on 12/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyCell : NSObject


@property (readwrite, nonatomic, retain) NSString *label;
@property (readwrite, nonatomic, retain) NSString *detail;

-(id) initWithLabel:(NSString *) l andWithDetail:(NSString *) d;

@end
