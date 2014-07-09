//
//  TaskView.m
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "TaskView.h"

@implementation TaskView

- (id)initWithFrame:(CGRect)frame
{
    myframe = frame;
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        isIpad = NO;
    } else {
        isIpad = YES;
    }

    self = [super initWithFrame:frame];
    if (self) {
        if (isIpad) {
            xOrig = 20;
            yOrig = 20;
            rapport = 2;
        } else {
            xOrig = 10;
            yOrig = 10;
            rapport = 1;
        }
        
        [self setBackgroundColor:[UIColor whiteColor]];
        prio =0;
        tab = [[NSArray alloc] initWithObjects:@"0", @"1", @"2", @"3", @"4", nil];
        select = [[UISegmentedControl alloc] initWithItems:tab];
        
        [select setSelectedSegmentIndex:0];
        [select addTarget:self action:@selector(setPrio) forControlEvents:UIControlEventAllEvents];
        [self addSubview:select];
        [select release];
        
        title = [[UILabel alloc] init];
        [title setText:@"Title : "];
        [self addSubview:title];
        
        priority = [[UILabel alloc] init];
        [priority setText:@"Priority : "];
        [self addSubview:priority];
        
        text = [[UITextField alloc] init];
        [text setBackgroundColor:[UIColor grayColor]];
        [text setText:[[self cell] label]];
        [text setDelegate:self];
        [self addSubview:text];
        
        photo = [[UIImage alloc] init];
    }
    return self;
}




-(BOOL)textFieldShouldReturn:(UITextField *)textField{
    titleStr = [textField text];
    [[self cell] setLabel:titleStr];
    [textField resignFirstResponder];
    return YES;
}

-(void) setFromOrientation:(UIInterfaceOrientation) o{
    if (o == UIInterfaceOrientationLandscapeLeft ||
        o == UIInterfaceOrientationLandscapeRight) {
        
        heigth = myframe.size.width;
        width = myframe.size.height;
        
        [text setText:[[self cell] label]];
        
        [select setFrame:CGRectMake(xOrig, heigth/2, width-2*xOrig, 50)];
        [text setFrame:CGRectMake(xOrig, heigth/2 -100, width-2*xOrig, 50)];
        [title setFrame:CGRectMake(xOrig, heigth/2 -140, 150, 30)];
        [priority setFrame:CGRectMake(xOrig, heigth/2 -40, 150, 30)];
    }
    else {
        width = myframe.size.width;
        heigth = myframe.size.height;
        
        [text setText:[[self cell] label]];
        
        [select setFrame:CGRectMake(xOrig, heigth/2, width-2*xOrig, 50)];
        [text setFrame:CGRectMake(xOrig, heigth/2 -100, width-2*xOrig, 50)];
        [title setFrame:CGRectMake(xOrig, heigth/2 -140, 150, 30)];
        [priority setFrame:CGRectMake(xOrig, heigth/2 -40, 150, 30)];
    }


}

-(void) setPrio{
    prio = [select selectedSegmentIndex];
    
    [[self cell] setPastille:[UIImage imageNamed:[NSString stringWithFormat:@"fullactivities-elements/prio%d.png", prio]]];
    NSLog(@"%@",[[[self cell] pastille] description]);
    [[self cell] setDetail:[NSString stringWithFormat:@"Priorité : %d",prio]];
    
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
