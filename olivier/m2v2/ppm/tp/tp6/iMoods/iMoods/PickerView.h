//
//  PickerView.h
//  iMoods
//
//  Created by m2sar on 12/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PickerView : UIView<UIPickerViewDataSource, UIPickerViewDelegate> {
    
    CGRect frame;
    UIPickerView* picker;
    NSArray* moods;
    
}

@property (readwrite, nonatomic, assign) NSString* currentMood;

- (void) setFromOrientation:(UIInterfaceOrientation)o;

- (void) updateMood;

@end
