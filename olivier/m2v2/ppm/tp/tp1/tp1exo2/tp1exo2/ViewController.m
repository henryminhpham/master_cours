//
//  ViewController.m
//  tp1exo2
//
//  Created by m2sar on 23/11/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

const int MAX = 99;
int value = 0;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) updateAll
{
    _dizaine.selectedSegmentIndex = value / 10;
    _unite.selectedSegmentIndex = value % 10;
    [_slide setValue:(value) animated:YES];
    [_stepper setValue:value];
    if(value == 42) {
        [_label setTextColor:[UIColor redColor]];
    } else {
        [_label setTextColor:[UIColor blackColor]];
    }
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }
}

- (IBAction)geekMode:(UISwitch *)sender {
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }
}

- (IBAction)reset:(UIButton *)sender {
    value = 0;
    [self updateAll];
    /*value = 0;
    [_label setTextColor:[UIColor blackColor]];
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }
    _dizaine.selectedSegmentIndex = 0;
    _unite.selectedSegmentIndex = 0;
    [_slide setValue:(0) animated:YES];
    [_stepper setValue:value];*/
}

- (IBAction)dizaineAction:(UISegmentedControl *)sender {
    value = (value % 10) + 10 * [_dizaine selectedSegmentIndex];
    [self updateAll];
    /*if(value == 42) {
        [_label setTextColor:[UIColor redColor]];
    } else {
        [_label setTextColor:[UIColor blackColor]];
    }
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }
    _unite.selectedSegmentIndex = value % 10;
    [_slide setValue:(value) animated:YES];
    [_stepper setValue:value];*/
}

- (IBAction)uniteAction:(UISegmentedControl *)sender {
    value = value - (value % 10) + [_unite selectedSegmentIndex];
    [self updateAll];
    /*if(value == 42) {
        [_label setTextColor:[UIColor redColor]];
    } else {
        [_label setTextColor:[UIColor blackColor]];
    }
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }
    _dizaine.selectedSegmentIndex = value / 10;
    [_slide setValue:(value) animated:YES];
    [_stepper setValue:value];*/
}


- (IBAction)slideAction:(UISlider *)sender {
    value = (int) ([_slide value]);
    [self updateAll];
    /*if(value == 42) {
        [_label setTextColor:[UIColor redColor]];
    } else {
        [_label setTextColor:[UIColor blackColor]];
    }
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }
    _dizaine.selectedSegmentIndex = value / 10;
    _unite.selectedSegmentIndex = value % 10;
    [_slide setValue:(value) animated:YES];
    [_stepper setValue:value];*/
}

- (IBAction)stepperAction:(UIStepper *)sender {
    value = (int) [sender value];
    [self updateAll];
    /*_dizaine.selectedSegmentIndex = value / 10;
    _unite.selectedSegmentIndex = value % 10;
    [_slide setValue:(value) animated:YES];
    if(value == 42) {
        [_label setTextColor:[UIColor redColor]];
    } else {
        [_label setTextColor:[UIColor blackColor]];
    }
    if(_geek.on) {
        [_label setText:[NSString stringWithFormat:@"0x%x", value]];
    } else {
        [_label setText:[NSString stringWithFormat:@"%d", value]];
    }*/
}
@end
