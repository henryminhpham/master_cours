//
//  MapView.h
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface MapView : UIView {
    
    CGRect frame;
    MKMapView* mapView;
    UITextView* textView;
    UIImageView* background;
    CLLocationManager* locationManager;
    
}

- (void) resetText;

- (UITextView*) getTextView;

- (void) makePosition: (double) latitude :(double) longitude;

- (void) setFromOrientation:(UIInterfaceOrientation) o;

- (NSString*) getUrl;
@end
