//
//  PickerView.m
//  iMoods
//
//  Created by m2sar on 12/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "PickerView.h"

@implementation PickerView

- (id)initWithFrame:(CGRect)f
{
    self = [super initWithFrame:f];
    if (self) {
        frame = f;
        picker = [[UIPickerView alloc] init];
        [picker setDelegate:self];
        [picker setDataSource:self];
        [self addSubview:picker];
        [picker release];
    
         moods = [[NSArray arrayWithObjects:@"Happy",@"Sad",@"Angry",@"Blues", nil] retain];
        _currentMood = [moods objectAtIndex:0];
        [picker setShowsSelectionIndicator:YES];
        [self setBackgroundColor:[UIColor colorWithRed:0 green:255 blue:128 alpha:0.9]];
        
        [self setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    }
    return self;
}

-(void)setFromOrientation:(UIInterfaceOrientation)o{
    CGFloat width, height;
    if (o == UIInterfaceOrientationLandscapeLeft || o == UIInterfaceOrientationLandscapeRight) {
        height = frame.size.width;
        width = frame.size.height;
    } else {
        width = frame.size.width;
        height = frame.size.height;
    }
    [picker setFrame:CGRectMake(width/2-100, height/2 -81, 200, 162.0)];
}

- (NSInteger) numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger) pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return [moods count];
}

-(NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component{
    return [moods objectAtIndex:row];
}

-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component{
    _currentMood = [moods objectAtIndex:row];
}

- (void) updateMood {
    NSDictionary* dict = [NSDictionary dictionaryWithObject:_currentMood forKey:@"mood"];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"mood" object:self userInfo:dict];
}


- (void) dealloc {
    [moods release];
    moods = nil;
    [_currentMood release];
    _currentMood = nil;
    [super dealloc];
}

@end
