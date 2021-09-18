Scene: Untitled
Entities:
  - Entity: 12837192831273
    TagComponent:
      Tag: Box
    TransformComponent:
      Translation: [-0.476418555, 0.616269588, 0]
      Rotation: [0, 0, 1.56825137]
      Scale: [1, 1, 1]
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
    Rigidbody2DComponent:
      Type: Dynamic
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Density: 1
      Friction: 0.5
      Restitution: 0
      RestitutionThreshold: 0.5
  - Entity: 12837192831273
    TagComponent:
      Tag: Camera
    TransformComponent:
      Translation: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    CameraComponent:
      Camera:
        ProjectionType: 1
        PerspectiveFOV: 0.785398185
        PerspectiveNear: 0.00999999978
        PerspectiveFar: 1000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
      FixedAspectRatio: false
  - Entity: 12837192831273
    TagComponent:
      Tag: Ground
    TransformComponent:
      Translation: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [29.7999992, 0.200000003, 1]
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
    Rigidbody2DComponent:
      Type: Static
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Density: 1
      Friction: 0.5
      Restitution: 0
      RestitutionThreshold: 0.5