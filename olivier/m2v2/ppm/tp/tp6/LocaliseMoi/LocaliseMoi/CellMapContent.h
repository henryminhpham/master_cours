//
//  CellMapContent.h
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CellMapContent : NSObject<NSCoding>

@property (readwrite, nonatomic, strong) NSString* label;
@property (readwrite, nonatomic) double latitude;
@property (readwrite, nonatomic) double longitude;
@end
