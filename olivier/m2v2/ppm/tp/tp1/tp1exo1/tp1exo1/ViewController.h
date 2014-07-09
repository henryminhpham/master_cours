//
//  ViewController.h
//  tp1exo1
//
//  Created by m2sar on 23/11/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (weak, nonatomic) IBOutlet UIButton *button;
- (IBAction)buttonAction:(UIButton *)sender;

@end
