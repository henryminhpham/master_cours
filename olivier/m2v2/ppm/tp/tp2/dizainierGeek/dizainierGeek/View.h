#import <UIKit/UIKit.h>

@interface View : UIView {
    UILabel *geek_mode_label;
    UILabel *dizaine_label;
    UILabel *unite_label;
    UILabel *compute_label;
    
    UIStepper *stepper;
    
    UISwitch *isGeek;
    
    UISegmentedControl *dizaine;
    UISegmentedControl *unit;
    
    UISlider *slider;
}

@property (nonatomic, assign) BOOL isGeekMode;
@property (nonatomic, assign) int current_dizaine;
@property (nonatomic, assign) int current_unite;

-(void) update_value:(int)dizaine unite:(int)unit;
-(void) processEventDizaine:(id)sender;
-(void) processEventUnit:(id)sender;
-(void) processEventSlider:(id)sender;
-(void) processEventStepper:(id)sender;
-(void) switchToGeekMode:(id)sender;

@end
