#import "View.h"

@implementation View
@synthesize isGeekMode, current_dizaine, current_unite;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setBackgroundColor:[UIColor whiteColor]];
        dizaine_label = [[UILabel alloc] initWithFrame:CGRectMake(150, 150, 100, 15)];
        unite_label = [[UILabel alloc] initWithFrame:CGRectMake(150, 250, 100, 15)];
        geek_mode_label = [[UILabel alloc] initWithFrame:CGRectMake(150, 40, 100, 15)];
        compute_label = [[UILabel alloc] initWithFrame:CGRectMake(150, 350, 100, 15)];
        
        stepper = [[UIStepper alloc] initWithFrame:CGRectMake(10, 30, 50, 30)];
        [stepper addTarget:self action:@selector(processEventStepper:) forControlEvents:UIControlEventValueChanged];
        
        isGeek = [[UISwitch alloc] initWithFrame:CGRectMake(250, 30, 100, 30)];
        [isGeek addTarget:self action:@selector(switchToGeekMode:) forControlEvents:UIControlEventValueChanged];
        
        NSArray *itemArray = [NSArray arrayWithObjects: @"0", @"1", @"2", @"3", @"4", @"5", @"6", @"7", @"8", @"9", nil];
        dizaine = [[UISegmentedControl alloc] initWithItems:itemArray];
        [dizaine setFrame:CGRectMake(10, 175, 300, 30)];
        [dizaine addTarget:self action:@selector(processEventDizaine:) forControlEvents:UIControlEventValueChanged];
        
        unit = [[UISegmentedControl alloc] initWithItems:itemArray];
        [unit setFrame:CGRectMake(10, 275, 300, 30)];
        [unit addTarget:self action:@selector(processEventUnit:) forControlEvents:UIControlEventValueChanged];
        
        slider = [[UISlider alloc] initWithFrame:CGRectMake(10, 315, 300, 30)];
        [slider setMaximumValue:100];
        [slider setMinimumValue:0];
        [slider addTarget:self action:@selector(processEventSlider:) forControlEvents:UIControlEventValueChanged];
        
        [dizaine_label setText:@"Dizaines"];
        [unite_label setText:@"Unités"];
        [geek_mode_label setText:@"Geek Mode"];
        [compute_label setText:@"0"];
        
        [self addSubview:dizaine_label];
        [self addSubview:unite_label];
        [self addSubview:geek_mode_label];
        [self addSubview:compute_label];
        
        [self addSubview:stepper];
        
        [self addSubview:isGeek];
        
        [self addSubview:dizaine];
        [self addSubview:unit];
        
        [self addSubview:slider];
    }
    return self;
}



- (void)update_value:(int)new_dizaine unite:(int)new_unite {
    self.current_dizaine = new_dizaine;
    self.current_unite = new_unite;
    
    int computed = new_dizaine * 10 + new_unite;
    
    [self->slider setValue:computed];
    [self->stepper setValue:computed];
    [self->unit setSelectedSegmentIndex:new_unite];
    [self->dizaine setSelectedSegmentIndex:new_dizaine];
    [self->slider setValue:computed animated:YES];
    
    if(computed == 42) {
        [self->compute_label setTextColor:[UIColor redColor]];
    } else {
        [self->compute_label setTextColor:[UIColor blackColor]];
    }
    
    if (self.isGeekMode) {
        [self->compute_label setText:[NSString stringWithFormat:@"%x", computed]];
    } else{
        [self->compute_label setText:[NSString stringWithFormat:@"%d", computed]];
    }
    
}


-(void) processEventStepper:(id)sender{
    int unite = (int)[stepper value] % 10;
    int dizain = [stepper value] / 10;
    
    [self update_value:dizain unite:unite];
}


- (void)processEventSlider:(id)sender {
    int unite = (int)[slider value] % 10;
    int dizain = [slider value] / 10;
    
    [self update_value:dizain unite:unite];
}

-(void) processEventUnit:(id)sender{
    [self update_value:self.current_dizaine unite:[unit selectedSegmentIndex]];
}

-(void) processEventDizaine:(id)sender{
    [self update_value:[dizaine selectedSegmentIndex] unite:self.current_unite];
}

- (void)switchToGeekMode:(id)sender {
    self.isGeekMode = ! self.isGeekMode;
    [self update_value:self.current_dizaine unite:self.current_unite];
}
@end
