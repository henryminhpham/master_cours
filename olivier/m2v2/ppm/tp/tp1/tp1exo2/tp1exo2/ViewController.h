//
//  ViewController.h
//  tp1exo2
//
//  Created by m2sar on 23/11/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UISegmentedControl *dizaine;
@property (weak, nonatomic) IBOutlet UISegmentedControl *unite;
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (weak, nonatomic) IBOutlet UISwitch *geek;
@property (weak, nonatomic) IBOutlet UISlider *slide;
@property (weak, nonatomic) IBOutlet UIStepper *stepper;


- (IBAction)reset:(UIButton *)sender;
- (IBAction)dizaineAction:(UISegmentedControl *)sender;
- (IBAction)uniteAction:(UISegmentedControl *)sender;
- (IBAction)geekMode:(UISwitch *)sender;
- (IBAction)slideAction:(UISlider *)sender;
- (IBAction)stepperAction:(UIStepper *)sender;
- (void) updateAll;
@end
