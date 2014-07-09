#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    view = [[View alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [[self view] addSubview: view];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)o
                                 duration:(NSTimeInterval)d{
    [view setFromOrientation:o];
}

- (void) didRotateToInterfaceOrientation:(UIInterfaceOrientation)o{
    [view setFromOrientation:o];
}


@end
