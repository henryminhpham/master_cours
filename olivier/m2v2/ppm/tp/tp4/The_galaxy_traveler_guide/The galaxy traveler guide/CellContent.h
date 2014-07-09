//
//  CellContent.h
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CellContent : NSObject

@property (readwrite, nonatomic, retain) NSString *label;
@property (nonatomic, retain) UIImage *img;
@property (readwrite, nonatomic, assign) NSString *hasAcces;

-(id)initWithLabel:(NSString *) l andWithBool:(BOOL) b andPlanetNumber:(int) i;

@end
