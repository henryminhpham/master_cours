//
//  cross.m
//  iSouvenir
//
//  Created by m2sar on 06/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "cross.h"

@implementation cross

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
        width = frame.size.width;
        heigth = frame.size.height;
        
        nord = CGPointMake(width/2, heigth/2-10);
        sud = CGPointMake(width/2, heigth/2-10);
        est = CGPointMake(width/2, heigth/2-10);
        ouest = CGPointMake(width/2, heigth/2-10);
        
        [self drawRect:rect withlinewidth:1 from:nord to:sud ];
        [self drawRect:rect withlinewidth:1 from:est to:ouest ];
        [self setNeedsDisplay];
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

- (void)drawRect:(CGRect)rect withlinewidth:(long)lineWidth from:(CGPoint)pStart to:(CGPoint)pEnd
{
    //line1
    CGContextRef context = UIGraphicsGetCurrentContext();
    NSLog(@"drawRect called");
    CGContextSetLineWidth(context, lineWidth);
    CGContextMoveToPoint(context, pStart.x, pStart.y);
    CGContextAddLineToPoint(context, pEnd.x, pEnd.y);
    CGContextSetRGBStrokeColor(context, 1, 0, 0, 1);
    CGContextStrokePath(context);
}

@end
