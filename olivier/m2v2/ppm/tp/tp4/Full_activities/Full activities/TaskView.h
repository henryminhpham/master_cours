//
//  TaskView.h
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CellContent.h"

@interface TaskView : UIView <UITextFieldDelegate>{
    UISegmentedControl *select;
    UITextField *text;
    UILabel *title, *priority;
    UIImage *photo;
    CGRect myframe;
    NSInteger prio;
    NSString *titleStr;
    BOOL isIpad;
    int xOrig, yOrig, rapport, heigth, width;
    NSArray *tab;
    
    
}
@property(nonatomic, retain) CellContent *cell;

-(void) setFromOrientation:(UIInterfaceOrientation) o;

@end
