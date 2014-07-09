//
//  MapView.m
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "MapView.h"

@implementation MapView

- (id)initWithFrame:(CGRect)f
{
    self = [super initWithFrame:f];
    if (self) {
        background = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"fond-terre.jpg"]];
        [self addSubview:background];
        [background release];
        frame = f;
        
        textView = [[UITextView alloc] init];
        [textView setTextColor:[UIColor purpleColor]];
        [textView setBackgroundColor:[UIColor grayColor]];
        [self addSubview:textView];
        [textView release];
        if([CLLocationManager locationServicesEnabled]) {
            mapView = [[MKMapView alloc] init];
            [mapView setScrollEnabled:YES];
            [mapView setZoomEnabled:YES];
            [self addSubview:mapView];
            [self makePosition:48.8464 :2.3548];
        } else {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Erreur" message:@"Localisation désactivée" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
    }
    return self;
}

- (UITextView*) getTextView {
    return textView;
}

- (void) resetText{
    [textView setText:@""];
}

- (void) makePosition: (double) latitude :(double) longitude {
    MKCoordinateRegion region;
    region.center.longitude = longitude;
    region.center.latitude = latitude;
    region.span.latitudeDelta = 0.15;
    region.span.longitudeDelta = 0.15;
    [mapView setRegion:region animated:YES];
}

- (NSString*) getUrl {
    return [textView text];
}

-(void) setFromOrientation:(UIInterfaceOrientation) o {
    CGFloat width, height;
    if (o == UIInterfaceOrientationLandscapeLeft || o == UIInterfaceOrientationLandscapeRight) {
        height = frame.size.width;
        width = frame.size.height;
    } else {
        width = frame.size.width;
        height = frame.size.height;
    }
    width -= 40;
    height -= 20;
    [textView setFrame:CGRectMake(20, 100, width, 50)];
    [mapView setFrame:CGRectMake(20, 170, width, height * 2 / 3)];
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
