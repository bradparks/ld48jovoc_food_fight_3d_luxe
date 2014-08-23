//
//  TKLaserNode.m
//  ConnWorlds
//
//  Created by Joel Davis on 8/23/14.
//  Copyright (c) 2014 Tapnik. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import "TKLaserNode.h"

#include "TKUseful.h"


@interface TKLaserNode ()
{
    SKSpriteNode *_beamNode;
    SKShapeNode *_dbgSegStart;
    SKShapeNode *_dbgSegEnd;
}

@property (nonatomic, readwrite) CGPoint segmentA;
@property (nonatomic, readwrite) CGPoint segmentB;

@end

@implementation TKLaserNode

- (id) init
{
    self = [super init];
    if (self)
    {
        _beamNode = [SKSpriteNode spriteNodeWithImageNamed: @"beam.png"];
        
        _beamNode.anchorPoint = CGPointMake( 0.0, 0.5 );
        self.position = CGPointMake( 385.0, 571 );
        _beamNode.color = [SKColor redColor];
        _beamNode.colorBlendFactor = 1.0;
        
        [self addChild: _beamNode];
        
//        self.xScale = 4.0;
        
        _dbgSegStart = [[SKShapeNode alloc] init];
        _dbgSegEnd = [[SKShapeNode alloc] init];
        
        CGPathRef circlePath = CGPathCreateMutable();
        CGPathAddEllipseInRect( circlePath , NULL , CGRectMake( -10,-10,20,20 ) );

        _dbgSegStart.path = circlePath;
        _dbgSegStart.fillColor = [SKColor blueColor];
        _dbgSegStart.zPosition = 2.0;

        _dbgSegEnd.path = circlePath;
        _dbgSegEnd.fillColor = [SKColor blueColor];
        _dbgSegEnd.zPosition = 2.0;
        
        CGPathRelease( circlePath);
        
        [self addChild: _dbgSegStart];
        [self addChild: _dbgSegEnd];
    }
    return self;
}

- (void) update: (CFTimeInterval) dt
{
    _beamNode.zRotation -= dt * (30.0 * (M_PI/180.0));
//    self.xScale = 1.0;
    
    // get the line's location for collision porpoises
    CGPoint dir = CGPointMake( cos( _beamNode.zRotation ),
                               sin( _beamNode.zRotation ) );
    
    CGPoint startPosition = CGPointMake( dir.x * _innerRadius.x ,
                                        dir.y * _innerRadius.y );
    
    CGPoint endPosition = CGPointMake( dir.x * 500, dir.y * 500 );

    _dbgSegStart.position = startPosition;
    _dbgSegEnd.position = endPosition;
    
    CGFloat beamScale = CGPointDist( CGPointZero, endPosition ) / 256.0;
    _beamNode.xScale = beamScale;
    
    self.segmentA = CGPointAdd( startPosition, self.position );
    self.segmentB = CGPointAdd( endPosition, self.position );

}

@end