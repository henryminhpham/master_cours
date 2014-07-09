//
//  CellContent.h
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CellContent : NSObject

@property (readwrite, nonatomic, retain) NSString *label;
@property (readwrite, nonatomic, retain) NSString *detail;
@property (nonatomic, retain) UIImage *pastille;

-(id) initWithLabel:(NSString *) l andWithDetail:(NSString *) d andWithPrio:(int) p;

@end
