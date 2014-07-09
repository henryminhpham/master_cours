#import "View.h"

@implementation View

const int MAX_WIDTH = 25;
const int MAX_HEIGHT = 25;
const int MAX_IMAGE = 19;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        if([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            _isIpad = NO;
        } else {
            _isIpad = YES;
        }
        _x_axis = 20;
        _y_axis = 20;
        
        backgroundView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"imagier-elements/fond-2048x2048.jpg"]];
        [self addSubview:backgroundView];
        
        imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"imagier-elements/photo-01.jpg"]];
        [imageView setFrame:CGRectMake(0, 0, [imageView bounds].size.width * 0.25, [imageView bounds].size.height*0.25)];
        resizableView = [[UIScrollView alloc] init];
        
        [resizableView setMaximumZoomScale:4.0];
        [resizableView setMinimumZoomScale:0.25];
        [resizableView setDelegate:self];
        [resizableView addSubview:imageView];
        [resizableView setContentSize:[imageView bounds].size];
        
        [self addSubview:resizableView];
        [resizableView release];
        [imageView release];
        
        photo_label = [[UILabel alloc] init];
        [photo_label setText:@"photo-01.jpg"];
        [self addSubview:photo_label];
        [photo_label release];
        
        stepper = [[UIStepper alloc] init];
        [stepper setMinimumValue:-1];
        [stepper addTarget:self action:@selector(processEventStepper:) forControlEvents:UIControlEventValueChanged];
        [self addSubview:stepper];
        [stepper release];
        
        widthSlider = [[UISlider alloc] init];
        [widthSlider setMaximumValue:400];
        [widthSlider setMinimumValue:25];
        [widthSlider setValue:100];
        [widthSlider addTarget:self action:@selector(processEventSlider:) forControlEvents:UIControlEventValueChanged];
        [self addSubview:widthSlider];
        
        heigthSlider = [[UISlider alloc] init];
        [heigthSlider setMaximumValue:400];
        [heigthSlider setMinimumValue:25];
        [heigthSlider setValue:100];
        [heigthSlider addTarget:self action:@selector(processEventSlider:) forControlEvents:UIControlEventValueChanged];
        [self addSubview:heigthSlider];
        
        width_label = [[UILabel alloc] init];
        [width_label setText:[NSString stringWithFormat:@"Largeur : %d",(int)[self->widthSlider value]]];
        [self addSubview:width_label];
        
        heigth_label = [[UILabel alloc] init];
        [heigth_label setText:[NSString stringWithFormat:@"Hauteur : %d",(int)[self->heigthSlider value]]];
        [self addSubview:heigth_label];
        
        [self setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    }
    return self;
}


-(void) processEventStepper:(id)sender{
    if ([stepper value] > MAX_IMAGE) {
        [stepper setValue:0];
    }
    if ([stepper value] < 0) {
        [stepper setValue:MAX_IMAGE];
    }
    [imageView removeFromSuperview];
    [resizableView removeFromSuperview];
    
    [widthSlider setValue:100];
    [heigthSlider setValue:100];
    [self->photo_label setText:[NSString stringWithFormat:@"photo-%02d.jpg",(int)[self->stepper value]+1]];
    
    [self->width_label setText:[NSString stringWithFormat:@"Largeur : %d",100]];
    [self->heigth_label setText:[NSString stringWithFormat:@"Hauteur : %d",100]];
    
    
    resizableView = [[UIScrollView alloc] initWithFrame:CGRectMake(_x_axis, 2 * _y_axis + 30, _width - 2 * _x_axis, _heigth - (_y_axis * 5 + 4 * 30))];
    [resizableView setMaximumZoomScale:4.0];
    [resizableView setMinimumZoomScale:0.25];
    [resizableView setDelegate:self];
    
    imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"imagier-elements/photo-%02d.jpg", (int)[stepper value]+1]]];
    [imageView setFrame:CGRectMake(0, 0, [imageView bounds].size.width * 0.25, [imageView bounds].size.height * 0.25)];
    
    [resizableView addSubview:imageView];
    [imageView release];
    [resizableView setContentSize:[imageView bounds].size];
    [self addSubview:resizableView];
    [resizableView release];
}

-(void) processEventSlider:(id)sender{
    [self->imageView removeFromSuperview];
    
    imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"imagier-elements/photo-%02d.jpg", (int)[stepper value]+1]]];
    
    if (widthSlider.value < MAX_WIDTH) {
        widthSlider.value = MAX_WIDTH;
    }
    if (heigthSlider.value < MAX_HEIGHT) {
        heigthSlider.value = MAX_HEIGHT;
    }
    
    [self->width_label setText:[NSString stringWithFormat:@"Largeur : %d",(int)[self->widthSlider value]]];
    [self->heigth_label setText:[NSString stringWithFormat:@"Hauteur : %d",(int)[self->heigthSlider value]]];
    
    CGFloat widthSliderValue = widthSlider.value / 100;
    CGFloat heigthSliderValue = heigthSlider.value / 100;
    
    [imageView setFrame:CGRectMake(0,0,([self->imageView bounds].size.width * widthSliderValue) * 0.1, ([self->imageView bounds].size.height * heigthSliderValue) * 0.1)];
    [resizableView addSubview:imageView];
    
    [imageView release];
    
}

- (void) setFromOrientation:(UIInterfaceOrientation) o {
    
    CGRect viewSize = [self bounds];
    _x_axis = 20;
    _y_axis = 20;
    
    if (o == UIInterfaceOrientationLandscapeLeft || o == UIInterfaceOrientationLandscapeRight){
        _heigth = viewSize.size.width;
        _width = viewSize.size.height;
    } else {
        _heigth = viewSize.size.height;
        _width = viewSize.size.width;
    }
    
    [imageView setFrame:CGRectMake(0, 0, [imageView bounds].size.width, [imageView bounds].size.height)];
    [resizableView setFrame:CGRectMake(_x_axis, 2*_y_axis+30, _width-2*_x_axis, _heigth-(_y_axis*5 +4*30 ))];
    [stepper setFrame:CGRectMake(_x_axis, _y_axis, 100, 30)];
    [width_label setFrame:CGRectMake(_x_axis, _heigth - (90+3*_y_axis), _width,30)];
    [heigth_label setFrame:CGRectMake(_x_axis, _heigth - (40+2*_y_axis), _width,30)];
    [photo_label setFrame:CGRectMake(_x_axis*2+100, _y_axis, _width-(2*_x_axis+50), 30)];
    [widthSlider setFrame:CGRectMake(_x_axis, _heigth - (30+30+3*_y_axis), _width - 2*_x_axis, 30)];
    [heigthSlider setFrame:CGRectMake(_x_axis, _heigth -(30+ _y_axis), _width - 2*_x_axis, 30)];
}

- (UIView*) viewForZoomingInScrollView:(UIScrollView *)scrollView{
    return imageView;
}

- (void) scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(CGFloat)scale{
    int realScale = (int) (scale * 100);
    [self->width_label setText:[NSString stringWithFormat:@"Largeur : %d",realScale]];
    [self->widthSlider setValue:realScale];
    
    [self->heigth_label setText:[NSString stringWithFormat:@"Hauteur : %d",realScale]];
    [self->heigthSlider setValue:realScale];
    
    
    if (widthSlider.value < MAX_WIDTH) {
        widthSlider.value = MAX_WIDTH;
    }
    if (heigthSlider.value < MAX_HEIGHT) {
        heigthSlider.value = MAX_HEIGHT;
    }
    
    CGFloat widthSliderValue = widthSlider.value / 100;
    CGFloat heigthSliderValue = heigthSlider.value / 100;
    
    [imageView setFrame:CGRectMake(0, 0, ([self->imageView bounds].size.width * widthSliderValue), ([self->imageView bounds].size.height * heigthSliderValue))];
    
    [resizableView addSubview:imageView];
    [resizableView setContentSize:[imageView bounds].size];
    
    
    [self->width_label setText:[NSString stringWithFormat:@"Largeur : %d",(int)[self->widthSlider value]]];
    [self->heigth_label setText:[NSString stringWithFormat:@"Hauteur : %d",(int)[self->heigthSlider value]]];
    
}


- (void) dealloc {
    
    [backgroundView release];
    [stepper release];
    [imageView release];
    [resizableView release];
    [photo_label release];
    [widthSlider release];
    [heigthSlider release];
    [width_label release];
    [heigth_label release];
    
    [super dealloc];
}

@end
